/**
 ******************************************************************************
 * @file		: interrupts.c
 * @author  	: KKI		kacper.krasin35@gmail.com
 * @version 	: 0.0.1
 * @date    	: Jan 12, 2024
 * @brief   	: Brief of source file
 *
 ******************************************************************************
 **/
#include "interrupts.h"

extern _AS5600_handle henc;
extern _PULSER_handle hpsr;
extern _MOTOR_handle hmtr;
extern _BUFFER_UARThandle hbfr;
extern _BUFFER_UARThandle hbfr2;
extern _BUFFER_ETHHandle hudp;
extern MenuHandle hmen;
extern _PID_handle hpid;
_PID_handle pid_temp = {
		.controller.Kp = 1.7f,
		.controller.Ki = 0.2f,
		.controller.Kd = 0.1f
};

FATFS fs;
FIL fil;
FRESULT fresult;
char parametry[64];
UINT bw;



void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if (htim->Instance == TIM5)
	{
		if (hbfr.active == 1)
		{
			hmen.state = hbfr.state;
			hmen.com = hbfr.com;
		}
		else if (hudp.active == 1)
		{
			hmen.state = hudp.state;
			hmen.com = hudp.com;
		}
		if (hmen.state == _DEBUG)
		{
			snprintf(hbfr2.rxBuffer, sizeof(hbfr2.rxBuffer), "Current value read from encoder: %f \r\n", henc.angle);
			send_uart(hbfr2.rxBuffer);
		}
		if (hmen.state == _DEBUG)
		{
			if ((hpsr.set_angle - 10) < henc.angle)
			{
				(MOTOR_SET_DECREASE(&hmtr) != HAL_OK) ? (_Error_Handler(__FILE__, __LINE__)): 1 ;
			}
			if ((hpsr.set_angle + 10) > henc.angle)
			{
				(MOTOR_SET_INCREASE(&hmtr) != HAL_OK) ? (_Error_Handler(__FILE__, __LINE__)): 1 ;
			}
		}
		if (hmen.state == _MANUAL)
		{
			pid_temp.current_angle = henc.angle;
			(PID_update(&hpid, &pid_temp) != HAL_OK) ? (_Error_Handler(__FILE__, __LINE__)): 1 ;
			PID_manualProcess(&hpid, &hmtr);
			__HAL_TIM_SET_AUTORELOAD(&htim4,hmtr.frequency);
		}
		if (hmen.state == _REMOTE)
		{
			if (hudp.newDataAvailable && sscanf(hudp.rx_buffer, "d%f", &hudp.value) == 1)
			{
				UDP_SendMessage(hudp.rx_buffer);
				//float32_t angle_from_matlab = atof(hudp.value);
				hpsr.set_angle = hudp.value;
				// Reset the flag or variable
				hudp.newDataAvailable = 0;
			}
			snprintf(hudp.rx_buffer, sizeof(hudp.rx_buffer), "%d,%d,%d",(uint8_t)henc.angle, (uint8_t)hpid.output, (uint8_t)hpid.lastError);
			UDP_SendMessage(hudp.rx_buffer);
		}
	}
	if (htim->Instance == TIM3)
	{

	    (AS5600_Angle(&henc) != HAL_OK) ? (_Error_Handler(__FILE__, __LINE__)): 1 ;


	}
}

//void HAL_ETH_RxCpltCallback(ETH_HandleTypeDef *heth)
//{
//
//}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if (huart == &huart3)
	{
		if (hbfr.rxBuffer[hbfr.rxIndex] == '\n' || hbfr.rxBuffer[hbfr.rxIndex] == '\r')
		{
			// End of command received
			hbfr.rxBuffer[hbfr.rxIndex] = '\0'; // Null-terminate the string
			hbfr.state = processCommand(hbfr.rxBuffer);

			// Reset buffer index for the next command
			hbfr.rxIndex = 0;

			// Restart UART reception
			HAL_UART_Receive_IT(&huart3, (uint8_t *)hbfr.rxBuffer, 1);
		}
		else
		{
			// Continue receiving characters
			hbfr.rxIndex++;
			if (hbfr.rxIndex < MAX_BUFFER_SIZE - 1)
			{
				HAL_UART_Receive_IT(&huart3, (uint8_t *)&hbfr.rxBuffer[hbfr.rxIndex], 1);
			}
			else
			{
				// Handle buffer overflow (optional)
				hbfr.rxIndex = 0;
				HAL_UART_Receive_IT(&huart3, (uint8_t *)hbfr.rxBuffer, 1);
			}
		}
	}
}

//void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart){
//	if (huart == &huart3){
//		if (hmen.state == _DEBUG)
//		{
//			snprintf(hbfr2.rxBuffer, sizeof(hbfr2.rxBuffer), "Current value read from encoder: %f \r\n", henc.angle);
//			send_uart(hbfr2.rxBuffer);
//		}
//		HAL_UART_Receive_IT(&huart3, (uint8_t *)hbfr.rxBuffer, 1);
//	}
//}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if (GPIO_Pin == USER_Btn_Pin)
	{
		if (hmen.state == _IDLE)
		{
			(hbfr.active == 1) ? (hbfr.active = 0):(hbfr.active = 1);
			(hudp.active == 1) ? (hudp.active = 0):(hudp.active = 1);
			(hudp.active + hbfr.active == 2) ? (hudp.active = 0):1;
			(hudp.active + hbfr.active == 0) ? (hbfr.active = 1):1;
		}
		if (hmen.state == _DEBUG)
		{
			__HAL_TIM_SET_AUTORELOAD(&htim4,999);
			(MOTOR_SET_ENABLE(&hmtr) != HAL_OK) ? (_Error_Handler(__FILE__, __LINE__)): 1 ;
		}
		if (hmen.state == _MANUAL)
		{
			pid_temp.setpoint = hpsr.set_angle;
			(MOTOR_SET_ENABLE(&hmtr) != HAL_OK) ? (_Error_Handler(__FILE__, __LINE__)): 1 ;
			UDP_SendMessage("MANUAL");
		}
		if (hmen.state == _REMOTE)
		{
			HAL_GPIO_TogglePin(LD1_GPIO_Port, LD1_Pin);
			fresult = f_mount(&fs,"",0);
			fresult = f_open(&fil, "parametry.txt", FA_OPEN_ALWAYS | FA_READ | FA_WRITE);
			int parametry_len = sprintf (parametry,"kd=%f kd=%f kd=%f\n",hpid.controller.Kp,hpid.controller.Ki,hpid.controller.Kd);
			fresult = f_lseek(&fil,f_size(&fil));
			fresult = f_write(&fil,parametry,parametry_len,&bw);
			f_close(&fil);
			memset(&parametry,0,parametry_len);
			fresult = f_mount(NULL,"",1);

		}
	}
}
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
	hpsr.angle_overflow = ((int16_t)__HAL_TIM_GET_COUNTER(htim) * 45) / 10;
	hpsr.set_angle = (hpsr.angle_overflow < 0) ? (fmod(hpsr.angle_overflow, 360.0) + 360.0) : (fmod(hpsr.angle_overflow, 360.0));
}
