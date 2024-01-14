/*
 * rotpulser.h
 *
 *  Created on: Jan 14, 2024
 *      Author: kacpe
 */

#ifndef INC_ROTPULSER_H_
#define INC_ROTPULSER_H_

#include "init.h"

typedef struct {
	float32_t set_angle;
	float32_t angle_overflow;
	GPIO_PinState button;
} _PULSER_handle;


#endif /* INC_ROTPULSER_H_ */
