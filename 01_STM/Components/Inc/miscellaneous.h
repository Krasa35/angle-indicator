/*
 * miscellaneous.h
 *
 *  Created on: Jan 13, 2024
 *      Author: Krasa
 */

#ifndef INC_MISCELLANEOUS_H_
#define INC_MISCELLANEOUS_H_

#include "init.h"
#include "menu_UART.h"
#include "eth_udp.h"
#include "motor.h"

/**
 * @file miscellaneous.h
 * @brief Header file for Miscellaneous functions.
 *
 * This file contains declarations for miscellaneous functions, including UART communication,
 * command processing, structure validity check, error handling, and peripheral initialization.
 */

/**
 * @brief Send a string through UART.
 *
 * @param[in] string Pointer to the string to be sent.
 */
void send_uart(const char* string);

/**
 * @brief Process a command received through UART.
 *
 * @param[in] command Pointer to the command string.
 * @return The menu state after processing the command.
 */
Menu_States processCommand(char* command);

/**
 * @brief Check if a structure contains NaN values.
 *
 * @param[in] structure Pointer to the structure.
 * @param[in] size Size of the structure in bytes.
 * @return Status of the operation.
 */
HAL_StatusTypeDef isStructContainsNAN(const void* structure, size_t size);

/**
 * @brief Error handler function.
 *
 * @param[in] file Name of the file where the error occurred.
 * @param[in] line Line number where the error occurred.
 */
void _Error_Handler(char* file, int line);

/**
 * @brief Initialize peripherals.
 */
void init_peripherals();

#endif /* INC_MISCELLANEOUS_H_ */
