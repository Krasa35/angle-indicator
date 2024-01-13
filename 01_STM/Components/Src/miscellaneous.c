/*
 * miscellaneous.c
 *
 *  Created on: Jan 13, 2024
 *      Author: kacpe
 */

#include "miscellaneous.h"

extern const MenuStrings menuStrings;

void send_uart (const char* string)
{
	uint8_t len = strlen(string);
	HAL_UART_Transmit(&huart3, (uint8_t *)string, len, 2000);
}

Menu_States processCommand(char *command)
{
	  Menu_States val;
	  if (strcmp(command, "DEBUG") == 0)
	  {
		// Handle Option 1
		send_uart(menuStrings._DEBUG);
		val = _DEBUG;
	  }
	  else if (strcmp(command, "REMOTE") == 0)
	  {
		// Handle Option 2
		send_uart(menuStrings._REMOTE);
		val = _REMOTE;
	  }
	  else if (strcmp(command, "MANUAL") == 0)
	  {
		// Handle Option 3
		send_uart(menuStrings._MANUAL);
		val = _MANUAL;
	  }
	  else
	  {
		// Invalid command
		send_uart("Invalid command\r\n");
		val = _IDLE;
	  }
  return val;
}
