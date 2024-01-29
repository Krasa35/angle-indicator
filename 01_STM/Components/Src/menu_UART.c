/**
 * @file menu_UART.c
 * @brief Implementation of UART menu and communication buffers
 * @date Jan 14, 2024
 * @author Krasa
 */

#include "menu_UART.h"

/** @brief Primary UART communication buffer handle */
_BUFFER_UARThandle hbfr = {
    .active = 0,
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
        ._MANUAL = "MANUAL",
        ._IDLE = "IDLE",
    }
};

/** @brief Secondary UART communication buffer handle */
_BUFFER_UARThandle hbfr2;
