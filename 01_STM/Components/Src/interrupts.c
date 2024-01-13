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
extern uint8_t* msg;
struct _hbufUART _buffer;

void _MODE_INIT(struct _MODE* handle){
	handle->_DEBUG = "DEBUG";
	handle->_MANUAL = "MANUAL";
	handle->_REMOTE = "REMOTE";
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	if (htim->Instance == TIM3) {
	  float zmienna = AS5600_Angle(&device);
	  char buffer[20];  // Adjust the size as needed
	  int len = snprintf(buffer, sizeof(buffer), "%f", zmienna);
	  buffer[len++] = '\r';
	  buffer[len++] = '\n';
	  //HAL_UART_Transmit(&huart3, (uint8_t *)buffer, len, 100);
	}
}

#define MAX_BUFFER_SIZE 64
char rxBuffer[MAX_BUFFER_SIZE];
uint8_t rxIndex = 0;

void processCommand(char *command);

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
//	_MODE_INIT(&_buffer.mode);
//	if (huart == &huart3)
//	{
//		sscanf(&msg, "%c", &_buffer.b);
//		if(_buffer.b != ';'){
//			_buffer.receivedBuffer[_buffer.bufferIndex++] = _buffer.b;
//		}
//		else{
//            // Reset the buffer and index
//			sscanf(&_buffer.receivedBuffer, _buffer.mode._DEBUG, &_buffer.temp);
//			if (){
//				HAL_UART_Transmit_IT(&huart3, _buffer.receivedBuffer, _buffer.bufferIndex);
//			}
//
//			for (int i = 0; i < _buffer.bufferIndex; i++){
//				_buffer.receivedBuffer[i] = 0;
//			}
//			_buffer.bufferIndex = 0;
//		}
//		HAL_UART_Receive_IT(&huart3, (uint8_t*)&msg, 1);
//	}
	if (huart == &huart3)
	  {
	    if (rxBuffer[rxIndex] == '\n' || rxBuffer[rxIndex] == '\r')
	    {
	      // End of command received
	      rxBuffer[rxIndex] = '\0'; // Null-terminate the string
	      processCommand(rxBuffer);

	      // Reset buffer index for the next command
	      rxIndex = 0;

	      // Restart UART reception
	      HAL_UART_Receive_IT(&huart3, (uint8_t *)rxBuffer, 1);
	    }
	    else
	    {
	      // Continue receiving characters
	      rxIndex++;
	      if (rxIndex < MAX_BUFFER_SIZE - 1)
	      {
	        HAL_UART_Receive_IT(&huart3, (uint8_t *)&rxBuffer[rxIndex], 1);
	      }
	      else
	      {
	        // Handle buffer overflow (optional)
	        rxIndex = 0;
	        HAL_UART_Receive_IT(&huart3, (uint8_t *)rxBuffer, 1);
	      }
	    }
	  }
}
void processCommand(char *command)
{
  if (strcmp(command, "1") == 0)
  {
    // Handle Option 1
    HAL_UART_Transmit_IT(&huart3, "Option 1 selected\r\n", strlen("Option 1 selected\r\n"));
  }
  else if (strcmp(command, "2") == 0)
  {
    // Handle Option 2
    HAL_UART_Transmit_IT(&huart3, "Option 2 selected\r\n", strlen("Option 2 selected\r\n"));
  }
  else
  {
    // Invalid command
    HAL_UART_Transmit_IT(&huart3, "Invalid command\r\n", strlen("Invalid command\r\n"));
  }
}
