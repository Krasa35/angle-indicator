/*
 * init.h
 *
 *  Created on: Jan 13, 2024
 *      Author: kacpe
 */

#ifndef INC_INIT_H_
#define INC_INIT_H_
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

typedef enum {
	_DEBUG 	= 	0,       	// Operation successful
	_REMOTE = 	1,    		// General error
	_MANUAL = 	2,     		// Device is busy
	_IDLE	=	9
} Menu_States;

typedef struct {
  const char *_DEBUG;
  const char *_REMOTE;
  const char *_MANUAL;
  const char *_IDLE;
} MenuStrings;

typedef struct {
  const char *_DEBUG;
  const char *_REMOTE;
  const char *_MANUAL;
  const char *_IDLE;
} MenuComs;

typedef struct {
	Menu_States state;
	MenuStrings compStrings;
	MenuComs	com;
} MenuHandle;



#endif /* INC_INIT_H_ */
