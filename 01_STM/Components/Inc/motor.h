/*
 * motor.h
 *
 *  Created on: Jan 14, 2024
 *      Author: Krasa
 */

#ifndef INC_MOTOR_H_
#define INC_MOTOR_H_

#include "init.h"
#include "miscellaneous.h"

/**
 * @file motor.h
 * @brief Header file for the Motor Control module.
 *
 * This file contains the declarations for the Motor Control module,
 * including the data structure definition and function prototypes.
 */

#define MOTOR_SET_ENABLE(__HANDLE__)    MOTOR_Enable(__HANDLE__, GPIO_PIN_RESET)
#define MOTOR_SET_DISABLE(__HANDLE__)   MOTOR_Enable(__HANDLE__, GPIO_PIN_SET)
#define MOTOR_SET_INCREASE(__HANDLE__)  MOTOR_Direction(__HANDLE__, GPIO_PIN_RESET)
#define MOTOR_SET_DECREASE(__HANDLE__)  MOTOR_Direction(__HANDLE__, GPIO_PIN_SET)

/**
 * @brief Data structure representing the Motor.
 */
typedef struct {
    GPIO_PinState enable_state;  /**< Motor enable state. */
    GPIO_PinState dir_state;     /**< Motor direction state. */
    float32_t error;             /**< Motor error. */
    float32_t freq_div;          /**< Motor frequency divider. */
} _MOTOR_handle;

/**
 * @brief Set the direction of the motor.
 *
 * @param[in] motor Pointer to the Motor data structure.
 * @param[in] enable Motor enable state (GPIO_PIN_RESET for enable, GPIO_PIN_SET for disable).
 * @return Status of the operation.
 */
HAL_StatusTypeDef MOTOR_Direction(_MOTOR_handle* motor, GPIO_PinState enable);

/**
 * @brief Enable or disable the motor.
 *
 * @param[in] motor Pointer to the Motor data structure.
 * @param[in] direction Motor direction state (GPIO_PIN_RESET for increase, GPIO_PIN_SET for decrease).
 * @return Status of the operation.
 */
HAL_StatusTypeDef MOTOR_Enable(_MOTOR_handle* motor, GPIO_PinState direction);

/**
 * @brief Find the motor frequency based on the difference.
 *
 * @param[in] motor Pointer to the Motor data structure.
 * @param[in] diff Frequency difference.
 * @return Status of the operation.
 */
HAL_StatusTypeDef MOTOR_FindFrequency(_MOTOR_handle* motor, float32_t diff);

#endif /* INC_MOTOR_H_ */
