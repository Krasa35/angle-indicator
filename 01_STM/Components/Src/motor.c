/*
 * motor.c
 *
 *  Created on: Jan 14, 2024
 *      Author: kacpe
 */

#include "motor.h"

_MOTOR_handle hmtr = {
		.enable_port = Enable_GPIO_Port,
		.enable_pin = Enable_Pin,
		.start = GPIO_PIN_RESET,
		.stop = GPIO_PIN_SET,
		.dir_port = Dir_GPIO_Port,
		.dir_pin = Dir_Pin,
		.dir_clockwise = GPIO_PIN_SET,
		.dir_anticlockwise = GPIO_PIN_RESET
//		.button = GPIO_PIN_RESET
};


void MOTOR_Direction(_MOTOR_handle* motor, GPIO_PinState direction)
{
	HAL_GPIO_WritePin(motor->dir_port, motor->dir_pin, direction);
}
void MOTOR_Enable(_MOTOR_handle* motor, GPIO_PinState enable)
{
	HAL_GPIO_WritePin(motor->enable_port, motor->enable_pin, enable);
}
