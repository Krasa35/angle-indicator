/*
 * AS5600.c
 *
 *  Created on: Jan 12, 2024
 *      Author: Kurus
 */

#include "AS5600.h"

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

HAL_StatusTypeDef AS5600_Angle(_AS5600_handle* encoder)
{
    uint16_t buffer;
    HAL_StatusTypeDef state = HAL_I2C_Mem_Read(&hi2c1, encoder->ADDRESS << 1, encoder->ANGLE1, 1, (uint8_t*)&buffer, 2, AS5600_MAX_DELAY);
    buffer = (buffer >> 8) | (buffer << 8); // zamiana bitow LH
    encoder->angle = buffer / 11.38;
    HAL_StatusTypeDef state = HAL_OK;
    return state;
}

HAL_StatusTypeDef AS5600_Magnes_Distance(_AS5600_handle* encoder){
	HAL_StatusTypeDef state = HAL_I2C_Mem_Read(&hi2c1, encoder->ADDRESS << 1, encoder->STATUS, 1, (uint8_t*)&encoder->magnes_distance, 1, AS5600_MAX_DELAY);
	return state;
}
