///*
// * AS5600.c
// *
// *  Created on: Jan 12, 2024
// *      Author: Kurus
// */
//
//#include "AS5600.h"
//
//void AS5600_Init(struct AS5600* device){
//    device->ADDRESS = _AS5600_ADDRESS;
//    device->ZMCO = 0;
//    device->ZPOS1 = 0;
//    device->ZPOS2 = 0;
//    device->MPOS1 = 0;
//    device->MPOS2 = 0;
//    device->MANG1 = 0;
//    device->MANG2 = 0;
//    device->CONF1 = 0;
//    device->CONF2 = 0;
//    device->RAW_ANGLE1 = 0;
//    device->RAW_ANGLE2 = 0;
//    device->ANGLE1 = _ANGLE;
//    device->ANGLE2 = 0;
//    device->STATUS = _STATUS;
//    device->AGC = 0;
//    device->MAGNITUDE1 = 0;
//    device->MAGNITUDE2 = 0;
//}
//float AS5600_Angle(struct AS5600* device)
//{
//    uint16_t angle;
//    HAL_I2C_Mem_Read(&hi2c1, device->ADDRESS << 1, device->ANGLE1, 1, (uint8_t*)&angle, 2, HAL_MAX_DELAY);
//    angle = (angle >> 8) | (angle << 8); // zamiana bitow LH
//    float angle_float = angle / 11.38;
//    return angle_float;
//}
//int AS5600_Magnes_Distance(struct AS5600* device)
//{
//    uint8_t magnes_distance;
//    HAL_I2C_Mem_Read(&hi2c1, device->ADDRESS << 1, device->STATUS, 1, (uint8_t*)&magnes_distance, 1, HAL_MAX_DELAY);
//    return magnes_distance;
//}
