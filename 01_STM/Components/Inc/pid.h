/*
 * pid.h
 *
 *  Created on: Jan 14, 2024
 *      Author: Krasa
 */

#ifndef INC_PID_H_
#define INC_PID_H_

#include "arm_math.h"
#include "AS5600.h"
#include "miscellaneous.h"
#include "motor.h"

#define MAX_BUFFER_SIZE 	64

/**
 * @file pid.h
 * @brief Header file for the Proportional-Integral-Derivative (PID) Controller module.
 *
 * This file contains the declarations for the PID Controller module,
 * including the data structure definition and function prototypes.
 */

/**
 * @brief PID Controller handle structure.
 *
 * This structure holds information and settings for the PID Controller module.
 */
typedef struct {
    arm_pid_instance_f32 controller; /**< ARM CMSIS-DSP PID controller instance. */
    float32_t setpoint;              /**< Target setpoint for the PID controller. */
    float error;                     /**< Current error between setpoint and actual value. */
    float lastError;                 /**< Previous error value. */
    float lastOutput;                /**< Previous output value. */
    float output;                    /**< Current output value of the PID controller. */
    float current_angle;             /**< Current angle used in the PID controller. */
    uint8_t at_dest;                 /**< Flag indicating if the system is at the destination. */
} _PID_handle;

/**
 * @brief Check if the system is at the destination.
 *
 * @param[in] pid Pointer to the PID handle structure.
 * @return #HAL_StatusTypeDef
 */
HAL_StatusTypeDef PID_check(_PID_handle* pid);

/**
 * @brief Perform one step of the PID control algorithm.
 *
 * @param[in] pid Pointer to the PID handle structure.
 * @param[out] errorMessage Pointer to store error message if needed.
 * @return #HAL_StatusTypeDef
 */
HAL_StatusTypeDef PID_Step(_PID_handle* pid, char* errorMessage);

/**
 * @brief Update PID parameters with new values.
 *
 * @param[in] pid Pointer to the PID handle structure to be updated.
 * @param[in] pid_new Pointer to the new PID handle structure.
 * @return #HAL_StatusTypeDef
 */
HAL_StatusTypeDef PID_update(_PID_handle* pid, const _PID_handle* pid_new);

/**
 * @brief Manually process the PID controller for motor control.
 *
 * @param[in] pid Pointer to the PID handle structure.
 * @param[in] mtr Pointer to the motor handle structure.
 * @return #HAL_StatusTypeDef
 */
HAL_StatusTypeDef PID_manualProcess(_PID_handle* pid, _MOTOR_handle* mtr);

#endif /* INC_PID_H_ */
