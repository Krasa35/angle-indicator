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
		.lastError = 0.0f,
		.setpoint = NAN,
		.output = 0.0f,
		.at_dest = 0
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
	pid->setpoint   = pid_new->setpoint;
	pid->current_angle = pid_new->current_angle;

    return HAL_OK;
}

HAL_StatusTypeDef PID_manualProcess(_PID_handle* pid, _MOTOR_handle* mtr){
	pid->error = pid->setpoint - pid->current_angle;
	if (pid->error > 0) {(pid->error < 180) ? 1:(pid->error = pid->error - 360);}
	if (pid->error < 0) {(pid->error < -180) ? (pid->error = pid->error + 360):1;}
	arm_pid_init_f32(&pid->controller, 1);
	pid->output = arm_pid_f32(&pid->controller, pid->error);
//	float32_t diff = (pid->output - pid->lastOutput)/0.001;
	GPIO_PinState dir = (pid->output < 0) ? (GPIO_PIN_SET):(GPIO_PIN_RESET);
	(MOTOR_Direction(mtr, dir) != HAL_OK) ? (_Error_Handler(__FILE__, __LINE__)): 1 ;
	(MOTOR_FindFrequency(mtr, pid->output) != HAL_OK) ? (_Error_Handler(__FILE__, __LINE__)): 1 ;
//	pid->lastOutput= pid->output;
	if (pid->at_dest) {(MOTOR_SET_ENABLE(mtr) != HAL_OK) ? (_Error_Handler(__FILE__, __LINE__)): 1 ;}
	if (abs(pid->error) < 1.0f){
		(MOTOR_SET_DISABLE(mtr) != HAL_OK) ? (_Error_Handler(__FILE__, __LINE__)): 1 ;
		pid->at_dest = 1;
	}
	return HAL_OK;
}
