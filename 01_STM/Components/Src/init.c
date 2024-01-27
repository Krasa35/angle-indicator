/*
 * init.c
 *
 *  Created on: Jan 13, 2024
 *      Author: kacpe
 */

#include "init.h"

MenuHandle hmen = {.state = _IDLE,
		.com = {
				._DEBUG = "ERROR! UNDEFINED VALUE",
				._REMOTE = "ERROR! UNDEFINED VALUE",
				._MANUAL = "ERROR! UNDEFINED VALUE",
				._IDLE = "ERROR! UNDEFINED VALUE",
			},
		.compStrings = {
				._DEBUG = "DEBUG",
				._REMOTE = "REMOTE",
				._MANUAL = "MANUAL",
				._IDLE = "IDLE",
			}
};
