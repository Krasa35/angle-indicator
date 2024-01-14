/*
 * init.c
 *
 *  Created on: Jan 13, 2024
 *      Author: kacpe
 */

#include "init.h"

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

_PULSER_handle hpsr = {
		.set_angle = 0.0,
		.angle_overflow = 0.0
};

_TIMER_IThandle htit;
