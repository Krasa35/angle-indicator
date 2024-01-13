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

extern struct AS5600 device;
extern float32_t set_angle;

extern _BUFFER_UARThandle hbfr;

// Initialize constant strings
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if (htim->Instance == TIM3)
	{
		float zmienna = AS5600_Angle(&device);
		if (hbfr.state == _DEBUG)
		{
			char buffer[20]; // Adjust the size as needed
			int len = snprintf(buffer, sizeof(buffer), "%f", zmienna);
			buffer[len++] = '\r';
			buffer[len++] = '\n';
			HAL_UART_Transmit(&huart3, (uint8_t *)buffer, len, 100);
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

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if (GPIO_Pin == USER_Btn_Pin)
	{
	}
}
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
	float32_t angle_overflow = ((int16_t)__HAL_TIM_GET_COUNTER(htim) * 45) / 10;
	set_angle = (angle_overflow < 0) ? (fmod(angle_overflow, 360.0) + 360.0) : (fmod(angle_overflow, 360.0));
}
