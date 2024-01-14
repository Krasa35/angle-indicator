/*
 * menu_UART.c
 *
 *  Created on: Jan 14, 2024
 *      Author: kacpe
 */

#include "menu_UART.h"

extern _MOTOR_handle hmtr;

_BUFFER_UARThandle hbfr = {
		.state = 9,
		.com = {
				._DEBUG = ACTIVATED(DEBUG),
				._REMOTE = ACTIVATED(REMOTE),
				._MANUAL = ACTIVATED(MANUAL),
				._IDLE = ACTIVATED(IDLE),
			},
		.compStrings = {
				  ._DEBUG = "DEBUG",
				  ._REMOTE = "REMOTE",
				  ._MANUAL = "MANUAL"
				}
};

_BUFFER_UARThandle hbfr2 = {
		.state = 9,
		.com = {
				._DEBUG = ACTIVATED(DEBUG),
				._REMOTE = ACTIVATED(REMOTE),
				._MANUAL = ACTIVATED(MANUAL),
				._IDLE = ACTIVATED(IDLE),
			},
		.compStrings = {
				  ._DEBUG = "DEBUG",
				  ._REMOTE = "REMOTE",
				  ._MANUAL = "MANUAL"
				}
};

HAL_StatusTypeDef BUFFER_Process()
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
		BUFFER_State_Inits();
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
return HAL_OK;
}
HAL_StatusTypeDef BUFFER_State_Inits()
{
	if (hbfr.state == _DEBUG)
	{
		MOTOR_Enable(&hmtr, hmtr.start);
		MOTOR_Direction(&hmtr, hmtr.dir_clockwise);
	}
	if (hbfr.state == _IDLE)
	{
		MOTOR_Enable(&hmtr, hmtr.stop);
	}
	return HAL_OK;
}

