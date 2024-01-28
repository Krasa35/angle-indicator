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

extern RTC_HandleTypeDef hrtc;

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
char Log[128], Time[16];
UINT bw;
RTC_TimeTypeDef sTime;


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if (htim->Instance == TIM5)
	{
		LCD_Display(hpsr.set_angle,henc.angle,&hmen);
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
			if (((hpsr.set_angle > henc.angle) && (hpsr.set_angle -  henc.angle < 180))||
					((hpsr.set_angle < henc.angle) && (henc.angle - hpsr.set_angle > 180)))
			{
				(MOTOR_SET_INCREASE(&hmtr) != HAL_OK) ? (_Error_Handler(__FILE__, __LINE__)): 1 ;
			}
			else
			{
				(MOTOR_SET_DECREASE(&hmtr) != HAL_OK) ? (_Error_Handler(__FILE__, __LINE__)): 1 ;
			}
		}
		if (hmen.state == _MANUAL)
		{
			pid_temp.current_angle = henc.angle;
			(PID_update(&hpid, &pid_temp) != HAL_OK) ? (_Error_Handler(__FILE__, __LINE__)): 1 ;
			PID_manualProcess(&hpid, &hmtr);
			__HAL_TIM_SET_AUTORELOAD(&htim4,hmtr.freq_div);
			__HAL_TIM_SET_PRESCALER(&htim4, 7199);
		}
		if (hmen.state == _REMOTE)
		{
			if (hudp.newDataAvailable && sscanf(hudp.rx_buffer, "y%f,p%f,i%f,d%f",
					&pid_temp.setpoint, &pid_temp.controller.Kp, &pid_temp.controller.Ki, &pid_temp.controller.Kd) == 1)
			{
				hpsr.set_angle = pid_temp.setpoint;
				hudp.newDataAvailable = 0;
			}
			pid_temp.current_angle = henc.angle;
			(PID_update(&hpid, &pid_temp) != HAL_OK) ? (_Error_Handler(__FILE__, __LINE__)): 1 ;
			PID_manualProcess(&hpid, &hmtr);
			__HAL_TIM_SET_AUTORELOAD(&htim4,hmtr.freq_div);
			__HAL_TIM_SET_PRESCALER(&htim4, 7199);

		}
		snprintf(hudp.rx_buffer, sizeof(hudp.rx_buffer), "%d,%d,%d",(uint16_t)henc.angle, (uint16_t)hpid.output, (uint16_t)hpid.error);
		UDP_SendMessage(hudp.rx_buffer);
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
		HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
		int16_t Log_length = 0;
		if (hmen.state == _IDLE)
		{
			(hbfr.active == 1) ? (hbfr.active = 0):(hbfr.active = 1);
			(hudp.active == 1) ? (hudp.active = 0):(hudp.active = 1);
			(hudp.active + hbfr.active == 2) ? (hudp.active = 0):1;
			(hudp.active + hbfr.active == 0) ? (hbfr.active = 1):1;
			int16_t parametry_len = sprintf (Log,"IDLE: Mode has been changed to command listen from %s",(hbfr.active == 1) ? ("UART.\n"):("ETH/UDP.\n"));
		    Log_length = Log_length + parametry_len;
		}
		if (hmen.state == _DEBUG)
		{
			__HAL_TIM_SET_AUTORELOAD(&htim4,999);
			(MOTOR_SET_ENABLE(&hmtr) != HAL_OK) ? (_Error_Handler(__FILE__, __LINE__)): 1 ;
			int16_t parametry_len = sprintf (Log,"DEBUG: Motor has been enabled. Timer AUTORELOAD: %d.\n", 999);
		    Log_length = Log_length + parametry_len;
		}
		if (hmen.state == _MANUAL)
		{
			pid_temp.setpoint = hpsr.set_angle;
			(MOTOR_SET_ENABLE(&hmtr) != HAL_OK) ? (_Error_Handler(__FILE__, __LINE__)): 1 ;
//			UDP_SendMessage("MANUAL");
			int16_t parametry_len = sprintf (Log,"MANUAL: Values for PID controller have been changed: Setpoint = %.2f, Kp = %.2f, Ki = %.2f, Kd = %.2f.\n",
											pid_temp.setpoint, pid_temp.controller.Kp,  pid_temp.controller.Ki,  pid_temp.controller.Kd);
		    Log_length = Log_length + parametry_len;
		}
		if (hmen.state == _REMOTE)
		{
			//HAL_GPIO_TogglePin(LD1_GPIO_Port, LD1_Pin);
			(MOTOR_SET_ENABLE(&hmtr) != HAL_OK) ? (_Error_Handler(__FILE__, __LINE__)): 1 ;
			int16_t parametry_len = sprintf (Log,"REMOTE: Listening to control from app.\n");
		    Log_length = Log_length + parametry_len;

		}
		fresult = f_mount(&fs,"",0);
		fresult = f_open(&fil, "Logs.txt", FA_OPEN_ALWAYS | FA_READ | FA_WRITE);
		int16_t data_len = sprintf (Time,"[%02d:%02d:%02d]",sTime.Hours, sTime.Minutes, sTime.Seconds);
		Log_length = Log_length + data_len;
		strcat(Time, Log);
		fresult = f_lseek(&fil,f_size(&fil));
		fresult = f_write(&fil,Time,Log_length,&bw);
		f_close(&fil);
		memset(&Log,0,Log_length);
		memset(&Time,0,data_len);
		fresult = f_mount(NULL,"",1);
	}
}
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
	if (hmen.state != _REMOTE){
		hpsr.angle_overflow = ((int16_t)__HAL_TIM_GET_COUNTER(htim) * 45) / 10;
		hpsr.set_angle = (hpsr.angle_overflow < 0) ? (fmod(hpsr.angle_overflow, 360.0) + 360.0) : (fmod(hpsr.angle_overflow, 360.0));
	}
}
