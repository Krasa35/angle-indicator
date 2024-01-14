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

extern _MOTOR_handle hmtr;
extern _PULSER_handle hpsr;
extern _BUFFER_UARThandle hbfr;
extern _BUFFER_UARThandle hbfr2;

// Initialize constant strings
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if (htim->Instance == TIM3)
	{
		AS5600_Angle(&henc);
		if (hbfr.state == _DEBUG)
		{
			snprintf(hbfr2.rxBuffer, sizeof(hbfr2.rxBuffer), "Current value read from encoder: %f \r\n", henc.angle);
			send_uart(hbfr2.rxBuffer);
		}
		if (hbfr.state == _DEBUG)
		{
			if ((hpsr.set_angle - 10) < henc.angle)
			{
				HAL_GPIO_WritePin(Dir_GPIO_Port, Dir_Pin, GPIO_PIN_SET);
			}
			if ((hpsr.set_angle + 10) > henc.angle)
			{
				HAL_GPIO_WritePin(Dir_GPIO_Port, Dir_Pin, GPIO_PIN_RESET);
			}
		}
	}
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if (huart == &huart3)
	{
		BUFFER_Process();
	}
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if (GPIO_Pin == USER_Btn_Pin)
	{
		char clearScreenSequence[] = "\x1B[2J";
		HAL_UART_Transmit(&huart3, (uint8_t *)clearScreenSequence, strlen(clearScreenSequence), HAL_MAX_DELAY);

	}
}
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
	hpsr.angle_overflow = ((int16_t)__HAL_TIM_GET_COUNTER(htim) * 45) / 10;
	hpsr.set_angle = (hpsr.angle_overflow < 0) ? (fmod(hpsr.angle_overflow, 360.0) + 360.0) : (fmod(hpsr.angle_overflow, 360.0));
}
