/*
 * miscellaneous.h
 *
 *  Created on: Jan 13, 2024
 *      Author: kacpe
 */

#ifndef INC_MISCELLANEOUS_H_
#define INC_MISCELLANEOUS_H_

#include "init.h"
#include "menu_UART.h"
#include "eth_udp.h"
#include "motor.h"

void send_uart (const char* string);
Menu_States processCommand(char *command);
HAL_StatusTypeDef isStructContainsNAN(const void* structure, size_t size);
void _Error_Handler(char *file, int line);
void init_peripherals();

#endif /* INC_MISCELLANEOUS_H_ */
