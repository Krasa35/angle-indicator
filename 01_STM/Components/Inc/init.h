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
#include "arm_math.h"
#include <stdio.h>

#include "init.h"
#include <string.h>

#define ACTIVATED(mode) ("%%---------------------------------%%\r\n\t\t" #mode " MODE ACTIVATED\r\n%%---------------------------------%%\r\n")

#define MAX_BUFFER_SIZE 	64
//#define ENCODER
#define MOTOR

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
  char rxBuffer[MAX_BUFFER_SIZE];
  uint8_t rxIndex;
  Menu_States state;
  MenuComs com;
  MenuStrings compStrings;
} _BUFFER_UARThandle;

typedef struct {
	float32_t set_angle;
	float32_t angle_overflow;
} _PULSER_handle;

typedef struct {
	float current_angle;
	char buffer[MAX_BUFFER_SIZE];
	int len;
} _TIMER_IThandle;


#endif /* INC_INIT_H_ */
