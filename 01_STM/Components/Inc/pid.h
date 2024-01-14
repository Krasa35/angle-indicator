/*
 * pid.h
 *
 *  Created on: Jan 14, 2024
 *      Author: kacpe
 */

#ifndef INC_PID_H_
#define INC_PID_H_

#include "arm_math.h"
#include "AS5600.h"
#include "miscellaneous.h"

#define MAX_BUFFER_SIZE 	64

typedef struct {
    arm_pid_instance_f32 controller;
    float setpoint;
    float integral;
    float lastError;
    float output;
    float current_angle;
} _PID_handle;

HAL_StatusTypeDef PID_check(_PID_handle* pid);
HAL_StatusTypeDef PID_Step(_PID_handle* pid, char* errorMessage);
HAL_StatusTypeDef PID_update(_PID_handle* pid, const _PID_handle* pid_new);

#endif /* INC_PID_H_ */
