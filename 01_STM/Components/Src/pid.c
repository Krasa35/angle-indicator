/**
 * @file pid.c
 * @brief PID controller implementation
 * @date Jan 14, 2024
 * @author Krasa
 */

#include "pid.h"

/**
 * @brief Default PID handle initialization with NaN values
 */
_PID_handle hpid = {
    .controller.Kp = NAN,
    .controller.Ki = NAN,
    .controller.Kd = NAN,
    .lastError = 0.0f,
    .setpoint = NAN,
    .output = 0.0f,
    .at_dest = 0
};

/**
 * @brief Check if PID handle contains NaN values
 * @param pid Pointer to the PID handle
 * @return HAL_OK if no NaN values, HAL_ERROR if NaN values are present
 */
HAL_StatusTypeDef PID_check(_PID_handle* pid)
{
    if (isStructContainsNAN(pid, sizeof(_PID_handle))) {
        // Handle the case where new parameters contain NaN
        return HAL_ERROR;
    } else {
        return HAL_OK;
    }
}

/**
 * @brief Update PID parameters with new values
 * @param pid Pointer to the PID handle to be updated
 * @param pid_new Pointer to the PID handle containing new parameters
 * @return HAL_OK if update is successful, HAL_ERROR if NaN values are present in the new parameters
 */
HAL_StatusTypeDef PID_update(_PID_handle* pid, const _PID_handle* pid_new)
{
    // Check if any parameter in pid_new is NaN
    if (isStructContainsNAN(pid_new, sizeof(_PID_handle))) {
        // Handle the case where new parameters contain NaN
        return HAL_ERROR;
    }

    // Update parameters
    pid->controller.Kp = pid_new->controller.Kp;
    pid->controller.Ki = pid_new->controller.Ki;
    pid->controller.Kd = pid_new->controller.Kd;
    pid->setpoint = pid_new->setpoint;
    pid->current_angle = pid_new->current_angle;

    return HAL_OK;
}

/**
 * @brief Manually process PID control and update motor output
 * @param pid Pointer to the PID handle
 * @param mtr Pointer to the motor handle
 * @return HAL_OK if successful
 */
HAL_StatusTypeDef PID_manualProcess(_PID_handle* pid, _MOTOR_handle* mtr)
{
    pid->error = pid->setpoint - pid->current_angle;
    if (pid->error > 0) {
        (pid->error < 180) ? 1 : (pid->error = pid->error - 360);
    }
    if (pid->error < 0) {
        (pid->error < -180) ? (pid->error = pid->error + 360) : 1;
    }
    arm_pid_init_f32(&pid->controller, 1);
    pid->output = arm_pid_f32(&pid->controller, pid->error);

    // Calculate direction based on output
    GPIO_PinState dir = (pid->output < 0) ? (GPIO_PIN_SET) : (GPIO_PIN_RESET);

    // Set motor direction
    (MOTOR_Direction(mtr, dir) != HAL_OK) ? (_Error_Handler(__FILE__, __LINE__)) : 1;

    // Set motor frequency based on PID output
    (MOTOR_FindFrequency(mtr, pid->output) != HAL_OK) ? (_Error_Handler(__FILE__, __LINE__)) : 1;

    // Enable motor if at destination
    if (pid->at_dest) {
        (MOTOR_SET_ENABLE(mtr) != HAL_OK) ? (_Error_Handler(__FILE__, __LINE__)) : 1;
    }

    // Disable motor if error is small
    if (fabs(pid->error) < 1.0f) {
        (MOTOR_SET_DISABLE(mtr) != HAL_OK) ? (_Error_Handler(__FILE__, __LINE__)) : 1;
        pid->at_dest = 1;
    }

    return HAL_OK;
}
