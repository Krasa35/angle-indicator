/*
 * rotpulser.c
 *
 *  Created on: Jan 14, 2024
 *      Author: kacpe
 */

#include "rotpulser.h"

_PULSER_handle hpsr = {
		.set_angle = 0.0,
		.angle_overflow = 0.0,
		.button = GPIO_PIN_RESET
};
