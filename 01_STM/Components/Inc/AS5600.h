/*
 * AS5600.h
 *
 *  Created on: Jan 12, 2024
 *      Author: Kurus
 */

#ifndef INC_AS5600_H_
#define INC_AS5600_H_

#include "stdint.h"
#include "i2c.h"

#define _AS5600_ADDRESS 0x36 //adres urzadzenia

//adresy rejestrow
#define _ZMCO 0x00
#define _ZPOS 0x01
#define _MPOS 0x03
#define _MANG 0x05
#define _CONF 0x07
#define _RAW_ANGLE 0x0C
#define _ANGLE 0x0E
#define _STATUS 0x0B
#define _AGC 0x1A
#define _MAGNITUDE 0x01B
//config

struct AS5600 {
    uint8_t ADDRESS;
    uint8_t    ZMCO;
    uint8_t    ZPOS1;
    uint8_t    ZPOS2;
    uint8_t    MPOS1;
    uint8_t    MPOS2;
    uint8_t    MANG1;
    uint8_t    MANG2;
    uint8_t    CONF1;
    uint8_t    CONF2;
    uint8_t    RAW_ANGLE1;
    uint8_t    RAW_ANGLE2;
    uint8_t    ANGLE1;
    uint8_t    ANGLE2;
    uint8_t    STATUS;
    uint8_t    AGC;
    uint8_t    MAGNITUDE1;
    uint8_t    MAGNITUDE2;
};

void AS5600_Init(struct AS5600* device);
float AS5600_Angle(struct AS5600* device);
int AS5600_Magnes_Distance(struct AS5600* device);

#endif /* INC_AS5600_H_ */
