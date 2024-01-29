/*
 * init.h
 *
 *  Created on: Jan 13, 2024
 *      Author: Krasa
 */

#ifndef INC_INIT_H_
#define INC_INIT_H_

// Include necessary libraries and header files
#include <OLD_AS5600.h>
#include "main.h"
#include "fatfs.h"
#include "fatfs_sd.h"
#include "i2c.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "usb_otg.h"
#include "gpio.h"

#include <stdlib.h>
#include <assert.h>

#include "arm_math.h"
#include <stdio.h>

#include "init.h"
#include <string.h>

// Enumeration for menu states
typedef enum {
    _DEBUG  =  0,        // Debug state
    _REMOTE =  1,        // Remote state
    _MANUAL =  2,        // Manual state
    _IDLE   =  9         // Idle state
} Menu_States;

// Structure for menu strings
typedef struct {
    const char *_DEBUG;
    const char *_REMOTE;
    const char *_MANUAL;
    const char *_IDLE;
} MenuStrings;

// Structure for menu commands
typedef struct {
    const char *_DEBUG;
    const char *_REMOTE;
    const char *_MANUAL;
    const char *_IDLE;
} MenuComs;

// Structure for menu handle
typedef struct {
    Menu_States state;
    MenuStrings compStrings;
    MenuComs    com;
} MenuHandle;

#endif /* INC_INIT_H_ */
