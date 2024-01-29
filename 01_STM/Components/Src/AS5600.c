/*
 * AS5600.c
 *
 *  Created on: Jan 12, 2024
 *      Author: Kurus
 */

/**
 * @file AS5600.c
 * @brief AS5600 Magnetic Encoder driver implementation.
 *
 * This file contains the implementation of the driver for the AS5600
 * Magnetic Encoder, which communicates over the I2C interface.
 */

#include "AS5600.h"

/**
 * @brief AS5600 handle structure.
 *
 * This structure holds information and configuration settings for the AS5600
 * Magnetic Encoder.
 */
_AS5600_handle henc = {
    .ADDRESS = _AS5600_ADDRESS,
    .ZMCO = 0,
    .ZPOS1 = 0,
    .ZPOS2 = 0,
    .MPOS1 = 0,
    .MPOS2 = 0,
    .MANG1 = 0,
    .MANG2 = 0,
    .CONF1 = 0,
    .CONF2 = 0,
    .RAW_ANGLE1 = 0,
    .RAW_ANGLE2 = 0,
    .ANGLE1 = _ANGLE,
    .ANGLE2 = 0,
    .STATUS = _STATUS,
    .AGC = 0,
    .MAGNITUDE1 = 0,
    .MAGNITUDE2 = 0,
    .angle = 0.0,
    .magnes_distance = 0
};

/**
 * @brief Read the angle from the AS5600.
 *
 * This function reads the angle data from the AS5600 Magnetic Encoder and
 * calculates the actual angle in degrees.
 *
 * @param encoder Pointer to the AS5600 handle structure.
 * @return Status of the I2C read operation.
 */
HAL_StatusTypeDef AS5600_Angle(_AS5600_handle* encoder)
{
    uint16_t buffer;
    HAL_StatusTypeDef state = HAL_I2C_Mem_Read(&hi2c1, encoder->ADDRESS << 1, encoder->ANGLE1, 1, (uint8_t*)&buffer, 2, AS5600_MAX_DELAY);
    buffer = (buffer >> 8) | (buffer << 8); // Swap LH bits
    encoder->angle = buffer / 11.38; // Calculate the angle in degrees
    return state;
}

/**
 * @brief Read the magnetic distance from the AS5600.
 *
 * This function reads the magnetic distance data from the AS5600 Magnetic Encoder.
 *
 * @param encoder Pointer to the AS5600 handle structure.
 * @return Status of the I2C read operation.
 */
HAL_StatusTypeDef AS5600_Magnes_Distance(_AS5600_handle* encoder){
    HAL_StatusTypeDef state = HAL_I2C_Mem_Read(&hi2c1, encoder->ADDRESS << 1, encoder->STATUS, 1, (uint8_t*)&encoder->magnes_distance, 1, AS5600_MAX_DELAY);
    return state;
}
