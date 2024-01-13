/**
  ******************************************************************************
  * @file		: interrupts.h
  * @author  	: KKI		kacper.krasin35@gmail.com
  * @version 	: 0.0.1
  * @date    	: Jan 12, 2024
  * @brief   	: Brief of source file
  *
  ******************************************************************************
**/

#ifndef INC_INTERRUPTS_H_
#define INC_INTERRUPTS_H_

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

#include "main.h"
#include <string.h>

#define MAX_STRING_LENGTH 255


struct _MODE
{
	char* _DEBUG;
	char* _REMOTE;
	char* _MANUAL;
};

typedef struct _hbufUART
{
	struct 	_MODE	mode;
	char 			b;
	char 			receivedBuffer[MAX_STRING_LENGTH];
	char			temp[MAX_STRING_LENGTH];
	uint8_t 		bufferIndex;
};

void _MODE_INIT(struct _MODE* handle);




#endif /* INC_INTERRUPTS_H_ */

//*****************************Brief Template*********************************//
//Name Of Function
/**
 * @brief 			@brief function
 * @param[in] 	  	name of @param 1		: Description
 * @retval 			name of @retval 		: Description
 */
