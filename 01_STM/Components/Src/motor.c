/**
 * @file motor.c
 * @brief Motor control implementation
 * @date Jan 14, 2024
 * @author Krasa
 */

#include "motor.h"

/**
 * @brief Default motor handle initialization
 */
_MOTOR_handle hmtr = {
    .enable_state = GPIO_PIN_SET,
    .dir_state = GPIO_PIN_RESET,
    .error = 0.0f,
    .freq_div = 0.0f,
};

/**
 * @brief Set the direction of the motor
 * @param motor Pointer to the motor handle
 * @param direction The direction to set (GPIO_PIN_SET for forward, GPIO_PIN_RESET for reverse)
 * @return HAL_OK if successful, HAL_ERROR if invalid pointers or NaN values are present
 */
HAL_StatusTypeDef MOTOR_Direction(_MOTOR_handle* motor, GPIO_PinState direction)
{
    if (motor == NULL || isStructContainsNAN(motor, sizeof(_MOTOR_handle))) {
        return HAL_ERROR;  // Invalid pointers or NaN values, function failed
    }
    HAL_GPIO_WritePin(Dir_GPIO_Port, Dir_Pin, direction);
    return HAL_OK;
}

/**
 * @brief Enable or disable the motor
 * @param motor Pointer to the motor handle
 * @param enable The state to set (GPIO_PIN_SET for enable, GPIO_PIN_RESET for disable)
 * @return HAL_OK if successful, HAL_ERROR if invalid pointers or NaN values are present
 */
HAL_StatusTypeDef MOTOR_Enable(_MOTOR_handle* motor, GPIO_PinState enable)
{
    if (motor == NULL || isStructContainsNAN(motor, sizeof(_MOTOR_handle))) {
        return HAL_ERROR;  // Invalid pointers or NaN values, function failed
    }
    HAL_GPIO_WritePin(Enable_GPIO_Port, Enable_Pin, enable);
    return HAL_OK;
}

/**
 * @brief Find motor frequency based on the difference in input values
 * @param motor Pointer to the motor handle
 * @param diff The difference in input values
 * @return HAL_OK if successful
 */
HAL_StatusTypeDef MOTOR_FindFrequency(_MOTOR_handle* motor, float32_t diff)
{
    float32_t dif;
    dif = (diff > 320) ? 320 : ((diff < -320) ? -320 : diff);
    motor->freq_div = floor(810 - fabs(dif) * 2.5);
    return HAL_OK;
}
