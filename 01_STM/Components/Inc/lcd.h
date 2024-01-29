/*
 * LCD.h
 *
 *  Created on: Jan 27, 2024
 *      Author: Kurus
 */

#ifndef INC_LCD_H_
#define INC_LCD_H_

#include "stdint.h"
#include "i2c.h"
#include "menu_UART.h"

#define I2C_ADDR 0x27 // I2C address of the PCF8574
#define RS_BIT 0 // Register select bit
#define EN_BIT 2 // Enable bit
#define BL_BIT 3 // Backlight bit
#define D4_BIT 4 // Data 4 bit
#define D5_BIT 5 // Data 5 bit
#define D6_BIT 6 // Data 6 bit
#define D7_BIT 7 // Data 7 bit

#define LCD_ROWS 2 // Number of rows on the LCD
#define LCD_COLS 16 // Number of columns on the LCD

/**
 * @brief Writes a nibble to the LCD.
 * @param[in] nibble The 4-bit nibble to be written.
 * @param[in] rs Register select bit.
 * @param[in] hi2c1 I2C handle.
 */
void lcd_Write_nibble(uint8_t nibble, uint8_t rs, I2C_HandleTypeDef *hi2c1);

/**
 * @brief Sends a command to the LCD.
 * @param[in] cmd The command to be sent.
 * @param[in] hi2c1 I2C handle.
 */
void LCD_Send_cmd(uint8_t cmd, I2C_HandleTypeDef *hi2c1);

/**
 * @brief Sends data to the LCD.
 * @param[in] data The data to be sent.
 * @param[in] hi2c1 I2C handle.
 */
void LCD_Send_data(uint8_t data, I2C_HandleTypeDef *hi2c1);

/**
 * @brief Initializes the LCD.
 * @param[in] hi2c1 I2C handle.
 */
void LCD_Init(I2C_HandleTypeDef *hi2c1);

/**
 * @brief Writes a string to the LCD.
 * @param[in] str The string to be written.
 * @param[in] hi2c1 I2C handle.
 */
void LCD_Write_string(char *str, I2C_HandleTypeDef *hi2c1);

/**
 * @brief Sets the cursor position on the LCD.
 * @param[in] row The row where the cursor should be set.
 * @param[in] column The column where the cursor should be set.
 * @param[in] hi2c1 I2C handle.
 */
void LCD_Set_cursor(uint8_t row, uint8_t column, I2C_HandleTypeDef *hi2c1);

/**
 * @brief Clears the LCD display.
 * @param[in] hi2c1 I2C handle.
 */
void LCD_Clear(I2C_HandleTypeDef *hi2c1);

/**
 * @brief Displays information on the LCD related to the specified angle and menu handle.
 * @param[in] zadany_kat The specified angle.
 * @param[in] odczytany_kat The read angle.
 * @param[in] hmen Menu handle.
 */
void LCD_Display(float zadany_kat, float odczytany_kat, MenuHandle* hmen);

#endif /* INC_LCD_H_ */
