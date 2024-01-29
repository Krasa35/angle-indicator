/*
 * menu_UART.h
 *
 *  Created on: Jan 14, 2024
 *      Author: Krasa
 */

#ifndef INC_MENU_UART_H_
#define INC_MENU_UART_H_

/**
 * @file menu_UART.h
 * @brief Header file for UART menu handling.
 *
 * This file contains declarations for handling UART menu functionality.
 */

#include "init.h"

#define ACTIVATED(mode) ("%%---------------------------------%%\r\n\t\t" #mode " MODE ACTIVATED\r\n%%---------------------------------%%\r\n")
#define MAX_BUFFER_SIZE 64

/**
 * @struct _BUFFER_UARThandle
 * @brief Structure for UART menu handling.
 */
typedef struct {
  int8_t active; /**< Indicates if the UART menu is active. */
  char rxBuffer[MAX_BUFFER_SIZE]; /**< Receive buffer for UART communication. */
  uint8_t rxIndex; /**< Index of the receive buffer. */
  Menu_States state; /**< Current state of the menu. */
  MenuComs com; /**< Menu command enumeration. */
  MenuStrings compStrings; /**< Structure containing completion strings. */
} _BUFFER_UARThandle;

#endif /* INC_MENU_UART_H_ */
