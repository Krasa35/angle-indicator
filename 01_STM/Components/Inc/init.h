/*
 * init.h
 *
 *  Created on: Jan 13, 2024
 *      Author: kacpe
 */

#ifndef INC_INIT_H_
#define INC_INIT_H_
#include "main.h"
#include "eth.h"
#include "fatfs.h"
#include "i2c.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "usb_otg.h"
#include "gpio.h"

#include "AS5600.h"
#include <stdio.h>

#include "init.h"
#include <string.h>

#define MAX_STRING_LENGTH 	255
#define MAX_BUFFER_SIZE 	64
#define TRUE				1
#define FALSE				0

typedef enum {
	_DEBUG 	= 	0,       	// Operation successful
	_REMOTE = 	1,    		// General error
	_MANUAL = 	2,     		// Device is busy
	_IDLE	=	4
} Menu_States;

typedef struct {
  const char *_DEBUG;
  const char *_REMOTE;
  const char *_MANUAL;
} MenuStrings;

typedef struct {
  MenuStrings menu;
  char rxBuffer[MAX_BUFFER_SIZE];
  uint8_t rxIndex;
  uint8_t _MAX_BUFFER_SIZE_;
  Menu_States state;
} _BUFFER_UARThandle;


#endif /* INC_INIT_H_ */
