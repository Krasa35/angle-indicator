/*
 * pid.c
 *
 *  Created on: Jan 14, 2024
 *      Author: kacpe
 */

#include "pid.h"

_PID_handle hpid = {
		.controller.Kp = NAN,
		.controller.Ki = NAN,
		.controller.Kd = NAN,
		.integral = NAN,
		.lastError = 0.0f,
		.setpoint = NAN,
		.output = 0.0f,
		.current_angle = NAN
};

HAL_StatusTypeDef PID_check(_PID_handle* pid)
{
    if (isStructContainsNAN(&pid, sizeof(_PID_handle))) {
        // Handle the case where new parameters contain NaN
        return HAL_ERROR;
    }else {
    	return HAL_OK;
    }
}

HAL_StatusTypeDef PID_update(_PID_handle* pid, const _PID_handle* pid_new) {
    // Check if any parameter in pid_new is NaN
    if (isStructContainsNAN(&pid_new, sizeof(_PID_handle))) {
        // Handle the case where new parameters contain NaN
        return HAL_ERROR;
    }

    // Update parameters
    pid->controller.Kp 		= pid_new->controller.Kp;
    pid->controller.Ki 		= pid_new->controller.Ki;
    pid->controller.Kd 		= pid_new->controller.Kd;
	pid->integral   = pid_new->integral;
	pid->setpoint   = pid_new->setpoint;
	pid->current_angle = pid_new->current_angle;

    return HAL_OK;
}

//HAL_StatusTypeDef PID_Step(_PID_handle* pid, char* errorMessage) {
//    if (pid == NULL) {
//        if (errorMessage != NULL) {
//            snprintf(errorMessage, MAX_BUFFER_SIZE, "Invalid pointers");
//        }
//        return HAL_ERROR;  // Invalid pointers, function failed
//    }
//    if (isStructContainsNAN(pid, sizeof(_PID_handle)))
//    {
//        if (errorMessage != NULL) {
//            snprintf(errorMessage, MAX_BUFFER_SIZE, "One of parameters has not been set -> NAN error");
//        }
//        return HAL_ERROR;  // Invalid pointers, function failed
//    }
//
//    float error = pid->setpoint - pid->current_angle;
//    pid->integral += error;
//    float derivative = error - pid->lastError;
//
//    pid->output = (pid->kp * error) + (pid->ki * pid->integral) + (pid->kd * derivative);
//    pid->lastError = error;
//
//    if (errorMessage != NULL) {
//        snprintf(errorMessage, MAX_BUFFER_SIZE, "No error");  // Provide a default message
//    }
//
//    return HAL_OK;  // Function executed correctly
//}
