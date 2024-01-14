/*
 * menu_UART.c
 *
 *  Created on: Jan 14, 2024
 *      Author: kacpe
 */

#include "menu_UART.h"

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

_BUFFER_UARThandle hbfr2;

