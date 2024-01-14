/*
 * miscellaneous.c
 *
 *  Created on: Jan 13, 2024
 *      Author: kacpe
 */

#include "miscellaneous.h"

extern _BUFFER_UARThandle hbfr;

void send_uart (const char* string)
{
	uint8_t len = strlen(string);
	HAL_UART_Transmit(&huart3, (uint8_t *)string, len, 2000);
}

Menu_States processCommand(char *command)
{
	  Menu_States val;
	  if (strcmp(command, hbfr.compStrings._DEBUG) == 0)
	  {
		// Handle Option 1
		send_uart(hbfr.com._DEBUG);
		val = _DEBUG;
	  }
	  else if (strcmp(command, hbfr.compStrings._REMOTE) == 0)
	  {
		// Handle Option 2
		send_uart(hbfr.com._REMOTE);
		val = _REMOTE;
	  }
	  else if (strcmp(command, hbfr.compStrings._MANUAL) == 0)
	  {
		// Handle Option 3
		send_uart(hbfr.com._MANUAL);
		val = _MANUAL;
	  }
	  else
	  {
		// Invalid command
		send_uart("Invalid command\r\n");
		send_uart(hbfr.com._IDLE);
		val = _IDLE;
	  }
  return val;
}

HAL_StatusTypeDef isStructContainsNAN(const void* structure, size_t size) {
    const uint8_t* ptr = (const uint8_t*)structure;
    const uint8_t* end = ptr + size;

    // Check for NaN in the binary representation of each float member
    while (ptr < end) {
        if (*ptr == 0xFF && *(ptr + 1) == 0xFF && *(ptr + 2) == 0xFF && *(ptr + 3) == 0xFF) {
            return HAL_ERROR;  // NaN found
        }
        ptr += sizeof(float);
    }

    return HAL_OK;  // No NaN found
}

void _Error_Handler(char *file, int line) {
    /* Your error handling code goes here */
    char errorMessage[100];  // Adjust the size based on your needs

    /* Format error message with file and line information */
    snprintf(errorMessage, sizeof(errorMessage), "Error in file %s at line %d\n", file, line);

    send_uart(errorMessage);

}
