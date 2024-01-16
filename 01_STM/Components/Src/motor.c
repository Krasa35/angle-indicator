/*
 * motor.c
 *
 *  Created on: Jan 14, 2024
 *      Author: kacpe
 */

#include "motor.h"

_MOTOR_handle hmtr = {
		.enable_state = GPIO_PIN_SET,
		.dir_state = GPIO_PIN_RESET,
//		.button = GPIO_PIN_RESET
		.error = 0.0f,
		.frequency = 0.0f,
};


HAL_StatusTypeDef MOTOR_Direction(_MOTOR_handle* motor, GPIO_PinState direction)
{
	if (motor == NULL) {
		return HAL_ERROR;  // Invalid pointers, function failed
	}
	if (isStructContainsNAN(motor, sizeof(_MOTOR_handle))) {
		return HAL_ERROR;  // Invalid pointers, function failed
	}
	HAL_GPIO_WritePin(Dir_GPIO_Port, Dir_Pin, direction);
	return HAL_OK;
}
HAL_StatusTypeDef MOTOR_Enable(_MOTOR_handle* motor, GPIO_PinState enable)
{
	if (motor == NULL) {
		return HAL_ERROR;  // Invalid pointers, function failed
	}
	if (isStructContainsNAN(motor, sizeof(_MOTOR_handle))) {
		return HAL_ERROR;  // Invalid pointers, function failed
	}
	HAL_GPIO_WritePin(Enable_GPIO_Port, Enable_Pin, enable);
	return HAL_OK;
}
HAL_StatusTypeDef MOTOR_FindFrequency(_MOTOR_handle* motor, float32_t diff){
	float32_t dif = (diff > 1000) ? (diff = 1000):diff;
	dif = (diff < -1000) ? (diff = -1000):diff;
	motor->frequency = floor((1000 - (dif/5))*999/1000);
	return HAL_OK;
}
