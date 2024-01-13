/*
 * init.c
 *
 *  Created on: Jan 13, 2024
 *      Author: kacpe
 */

#include "init.h"

const MenuStrings menuStrings = {
  ._DEBUG = "DEBUG",
  ._REMOTE = "REMOTE",
  ._MANUAL = "MANUAL"
};

_BUFFER_UARThandle hbfr = {
		.state = 9
};
