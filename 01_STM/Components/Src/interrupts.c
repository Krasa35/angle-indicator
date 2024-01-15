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
extern _PID_handle hpid;
_PID_handle pid_temp = {
		.controller.Kp = 1.7f,
		.controller.Ki = 0.2f,
		.controller.Kd = 0.1f
};


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if (htim->Instance == TIM3)
	{
	    (AS5600_Angle(&henc) != HAL_OK) ? (_Error_Handler(__FILE__, __LINE__)): 1 ;

	    if (hbfr.state == _DEBUG)
	    {
	    	snprintf(hbfr2.rxBuffer, sizeof(hbfr2.rxBuffer), "Current value read from encoder: %f \r\n", henc.angle);
	    	send_uart(hbfr2.rxBuffer);
	    }
		if (hbfr.state == _DEBUG)
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
		if (hbfr.state == _MANUAL)
		{
			pid_temp.current_angle = henc.angle;
			(PID_update(&hpid, &pid_temp) != HAL_OK) ? (_Error_Handler(__FILE__, __LINE__)): 1 ;
			PID_manualProcess(&hpid, &hmtr);
			__HAL_TIM_SET_AUTORELOAD(&htim4,hmtr.frequency);
		}
	}
}

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
//		if (hbfr.state == _DEBUG)
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
		if (hbfr.state == _DEBUG)
		{
			__HAL_TIM_SET_AUTORELOAD(&htim4,999);
			(MOTOR_SET_ENABLE(&hmtr) != HAL_OK) ? (_Error_Handler(__FILE__, __LINE__)): 1 ;
		}
		if (hbfr.state == _MANUAL)
		{
			pid_temp.setpoint = hpsr.set_angle;
			(MOTOR_SET_ENABLE(&hmtr) != HAL_OK) ? (_Error_Handler(__FILE__, __LINE__)): 1 ;
		}
	}
}
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
	hpsr.angle_overflow = ((int16_t)__HAL_TIM_GET_COUNTER(htim) * 45) / 10;
	hpsr.set_angle = (hpsr.angle_overflow < 0) ? (fmod(hpsr.angle_overflow, 360.0) + 360.0) : (fmod(hpsr.angle_overflow, 360.0));
}
