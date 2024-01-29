/**
 * @file miscellaneous.c
 * @brief Miscellaneous functions and peripheral initialization
 * @date Jan 13, 2024
 * @author Krasa
 */

#include "miscellaneous.h"

/** @brief Buffer for UART communication */
extern _BUFFER_UARThandle hbfr;

/** @brief Second buffer for UART communication */
extern _BUFFER_UARThandle hbfr2;

/** @brief UDP buffer handle */
extern _BUFFER_ETHHandle hudp;

/** @brief Motor handle */
extern _MOTOR_handle hmtr;

/**
 * @brief Transmit a string via UART
 * @param string The string to be transmitted
 */
void send_uart(const char* string)
{
    uint8_t len = strlen(string);
    HAL_UART_Transmit(&huart3, (uint8_t *)string, len, 200);
}

/**
 * @brief Initialize peripherals and start necessary timers and UART reception
 */
void init_peripherals()
{
    HAL_TIM_Encoder_Start_IT(&htim1, TIM_CHANNEL_ALL);
    HAL_UART_Receive_IT(&huart3, (uint8_t *)&hbfr.rxBuffer[hbfr.rxIndex], 1);
    HAL_TIM_Base_Start_IT(&htim3);
    HAL_TIM_Base_Start_IT(&htim5);
    HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_1);
    HAL_GPIO_WritePin(Dir_GPIO_Port, Dir_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(Enable_GPIO_Port, Enable_Pin, GPIO_PIN_SET);
    hudp.active = 0;
    hbfr.active = 1;
    hbfr2.active = 0;
    (MOTOR_SET_DISABLE(&hmtr) != HAL_OK) ? (_Error_Handler(__FILE__, __LINE__)) : 1;
}

/**
 * @brief Process a command and send corresponding response via UART
 * @param command The command string to be processed
 * @return The corresponding Menu_State based on the processed command
 */
Menu_States processCommand(char *command)
{
    Menu_States val;
    if (strcmp(command, hbfr.compStrings._DEBUG) == 0)
    {
        send_uart(hbfr.com._DEBUG);
        val = _DEBUG;
        (MOTOR_SET_DISABLE(&hmtr) != HAL_OK) ? (_Error_Handler(__FILE__, __LINE__)) : 1;
    }
    else if (strcmp(command, hbfr.compStrings._REMOTE) == 0)
    {
        send_uart(hbfr.com._REMOTE);
        val = _REMOTE;
        (MOTOR_SET_DISABLE(&hmtr) != HAL_OK) ? (_Error_Handler(__FILE__, __LINE__)) : 1;
    }
    else if (strcmp(command, hbfr.compStrings._MANUAL) == 0)
    {
        send_uart(hbfr.com._MANUAL);
        val = _MANUAL;
        (MOTOR_SET_DISABLE(&hmtr) != HAL_OK) ? (_Error_Handler(__FILE__, __LINE__)) : 1;
    }
    else if (strcmp(command, hbfr.compStrings._IDLE) == 0)
    {
        send_uart(hbfr.com._IDLE);
        val = _IDLE;
        (MOTOR_SET_DISABLE(&hmtr) != HAL_OK) ? (_Error_Handler(__FILE__, __LINE__)) : 1;
    }
    else {
        // Invalid command
        send_uart("Invalid command\r\n");
        val = _IDLE;
        (MOTOR_SET_DISABLE(&hmtr) != HAL_OK) ? (_Error_Handler(__FILE__, __LINE__)) : 1;
    }
    return val;
}

/**
 * @brief Check if a structure contains NaN values
 * @param structure Pointer to the structure
 * @param size Size of the structure in bytes
 * @return HAL_OK if no NaN values, HAL_ERROR if NaN values are present
 */
HAL_StatusTypeDef isStructContainsNAN(const void* structure, size_t size) {
    const uint8_t* ptr = (const uint8_t*)structure;
    const uint8_t* end = ptr + size;

    // Check for NaN in the binary representation of each float member
    while (ptr < end) {
        if (*ptr == 0xFF && *(ptr + 1) == 0xFF && *(ptr + 2) == 0xFF && *(ptr + 3) == 0xFF) {
            return HAL_ERROR;  // NaN found
        }
        ptr += sizeof(float);
    }

    return HAL_OK;  // No NaN found
}

/**
 * @brief Error handling function, transmits an error message via UART
 * @param file File name where the error occurred
 * @param line Line number where the error occurred
 */
void _Error_Handler(char *file, int line) {
    /* Your error handling code goes here */
    char errorMessage[100];  // Adjust the size based on your needs

    /* Format error message with file and line information */
    snprintf(errorMessage, sizeof(errorMessage), "Error in file %s at line %d\n", file, line);

    send_uart(errorMessage);
}
