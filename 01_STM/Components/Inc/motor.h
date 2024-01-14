/*
 * motor.h
 *
 *  Created on: Jan 14, 2024
 *      Author: kacpe
 */

#ifndef INC_MOTOR_H_
#define INC_MOTOR_H_

#include "init.h"

typedef struct {
	GPIO_TypeDef* 	enable_port;
	uint16_t 		enable_pin;
	GPIO_PinState 	start;
	GPIO_PinState 	stop;
	GPIO_TypeDef* 	dir_port;
	uint16_t 		dir_pin;
	GPIO_PinState 	dir_clockwise;
	GPIO_PinState 	dir_anticlockwise;
//	GPIO_PinState button = GPIO_PIN_RESET;
} _MOTOR_handle;

void MOTOR_Direction(_MOTOR_handle* motor, GPIO_PinState enable);
void MOTOR_Enable(_MOTOR_handle* motor, GPIO_PinState direction);

#endif /* INC_MOTOR_H_ */
