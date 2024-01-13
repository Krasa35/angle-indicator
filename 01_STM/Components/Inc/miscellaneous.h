/*
 * miscellaneous.h
 *
 *  Created on: Jan 13, 2024
 *      Author: kacpe
 */

#ifndef INC_MISCELLANEOUS_H_
#define INC_MISCELLANEOUS_H_
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

void send_uart (const char* string);
Menu_States processCommand(char *command);


#endif /* INC_MISCELLANEOUS_H_ */
