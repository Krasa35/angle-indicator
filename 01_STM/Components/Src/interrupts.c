/**
  ******************************************************************************
  * @file		: interrupts.c
  * @author  	: KKI		kacper.krasin35@gmail.com
  * @version 	: 0.0.1
  * @date    	: Jan 12, 2024
  * @brief   	: Brief of source file
  *
  ******************************************************************************
**/
#include "interrupts.h"

extern struct AS5600 device;
extern float32_t set_angle;

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	if (htim->Instance == TIM3){
	  float zmienna = AS5600_Angle(&device);
	  char buffer[20];  // Adjust the size as needed
	  int len = snprintf(buffer, sizeof(buffer), "%f", zmienna);
	  buffer[len++] = '\r';
	  buffer[len++] = '\n';
	  HAL_UART_Transmit(&huart3, (uint8_t *)buffer, len, 100);
	}
}
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
	float32_t angle_overflow = ((int16_t)__HAL_TIM_GET_COUNTER(htim)*45)/10;
	set_angle = (angle_overflow < 0) ? (fmod(angle_overflow, 360.0)+360.0):(fmod(angle_overflow, 360.0));
}
