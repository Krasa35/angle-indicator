/*
 * motor.h
 *
 *  Created on: Jan 14, 2024
 *      Author: kacpe
 */

#ifndef INC_MOTOR_H_
#define INC_MOTOR_H_

#define MOTOR_SET_ENABLE(__HANDLE__) 	MOTOR_Enable(__HANDLE__, GPIO_PIN_RESET)
#define MOTOR_SET_DISABLE(__HANDLE__) 	MOTOR_Enable(__HANDLE__, GPIO_PIN_SET)
#define MOTOR_SET_INCREASE(__HANDLE__)	MOTOR_Direction(__HANDLE__, GPIO_PIN_RESET)
#define MOTOR_SET_DECREASE(__HANDLE__)	MOTOR_Direction(__HANDLE__, GPIO_PIN_SET)

#include "init.h"
#include "miscellaneous.h"


typedef struct {
	GPIO_PinState 	enable_state;
	GPIO_PinState 	dir_state;
//	GPIO_PinState button = GPIO_PIN_RESET;
	float32_t error;
	float32_t frequency;
} _MOTOR_handle;

HAL_StatusTypeDef MOTOR_Direction(_MOTOR_handle* motor, GPIO_PinState enable);
HAL_StatusTypeDef MOTOR_Enable(_MOTOR_handle* motor, GPIO_PinState direction);
HAL_StatusTypeDef MOTOR_FindFrequency(_MOTOR_handle* motor, float32_t diff);

#endif /* INC_MOTOR_H_ */
