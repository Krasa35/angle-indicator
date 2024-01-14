/*
 * menu_UART.h
 *
 *  Created on: Jan 14, 2024
 *      Author: kacpe
 */

#ifndef INC_MENU_UART_H_
#define INC_MENU_UART_H_

#define ACTIVATED(mode) ("%%---------------------------------%%\r\n\t\t" #mode " MODE ACTIVATED\r\n%%---------------------------------%%\r\n")
#define MAX_BUFFER_SIZE 	64

#include "init.h"

typedef struct {
  char rxBuffer[MAX_BUFFER_SIZE];
  uint8_t rxIndex;
  Menu_States state;
  MenuComs com;
  MenuStrings compStrings;
} _BUFFER_UARThandle;

#endif /* INC_MENU_UART_H_ */
