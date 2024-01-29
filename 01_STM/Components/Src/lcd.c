/**
 * @file lcd.c
 * @brief Implementation of LCD functions using I2C communication
 * @date Jan 27, 2024
 * @author Kurus
 */

#include "lcd.h"

/**
 * @brief Write a nibble to the LCD using I2C
 * @param nibble The 4-bit data nibble to be written
 * @param rs Register select (0 for command, 1 for data)
 * @param hi2c1 Pointer to the I2C handle
 */
void LCD_Write_nibble(uint8_t nibble, uint8_t rs, I2C_HandleTypeDef *hi2c1) {
    uint8_t data = nibble << D4_BIT;
    data |= rs << RS_BIT;
    data |= 1 << BL_BIT;  // Include backlight state in data
    data |= 1 << EN_BIT;
    HAL_I2C_Master_Transmit(hi2c1, I2C_ADDR << 1, &data, 1, 100);
    data &= ~(1 << EN_BIT);
    HAL_I2C_Master_Transmit(hi2c1, I2C_ADDR << 1, &data, 1, 100);
}

/**
 * @brief Send a command to the LCD using I2C
 * @param cmd The command to be sent
 * @param hi2c1 Pointer to the I2C handle
 */
void LCD_Send_cmd(uint8_t cmd, I2C_HandleTypeDef *hi2c1) {
    uint8_t upper_nibble = cmd >> 4;
    uint8_t lower_nibble = cmd & 0x0F;
    LCD_Write_nibble(upper_nibble, 0, hi2c1);
    LCD_Write_nibble(lower_nibble, 0, hi2c1);
    if (cmd == 0x01 || cmd == 0x02) {
        //HAL_Delay(2);
    }
}

/**
 * @brief Send data to the LCD using I2C
 * @param data The data to be sent
 * @param hi2c1 Pointer to the I2C handle
 */
void LCD_Send_data(uint8_t data, I2C_HandleTypeDef *hi2c1) {
    uint8_t upper_nibble = data >> 4;
    uint8_t lower_nibble = data & 0x0F;
    LCD_Write_nibble(upper_nibble, 1, hi2c1);
    LCD_Write_nibble(lower_nibble, 1, hi2c1);
}

/**
 * @brief Initialize the LCD
 * @param hi2c1 Pointer to the I2C handle
 */
void LCD_Init(I2C_HandleTypeDef *hi2c1) {
    HAL_Delay(50);
    LCD_Write_nibble(0x03, 0, hi2c1);
    HAL_Delay(5);
    LCD_Write_nibble(0x03, 0, hi2c1);
    HAL_Delay(1);
    LCD_Write_nibble(0x03, 0, hi2c1);
    HAL_Delay(1);
    LCD_Write_nibble(0x02, 0, hi2c1);
    LCD_Send_cmd(0x28, hi2c1);
    LCD_Send_cmd(0x0C, hi2c1);
    LCD_Send_cmd(0x06, hi2c1);
    LCD_Send_cmd(0x01, hi2c1);
    HAL_Delay(2);
}

/**
 * @brief Write a string to the LCD
 * @param str The string to be written
 * @param hi2c1 Pointer to the I2C handle
 */
void LCD_Write_string(char *str, I2C_HandleTypeDef *hi2c1) {
    while (*str) {
        LCD_Send_data(*str++, hi2c1);
    }
}

/**
 * @brief Set the cursor position on the LCD
 * @param row The row to set the cursor on (0 or 1)
 * @param column The column to set the cursor on (0 to 15)
 * @param hi2c1 Pointer to the I2C handle
 */
void LCD_Set_cursor(uint8_t row, uint8_t column, I2C_HandleTypeDef *hi2c1) {
    uint8_t address;
    switch (row) {
        case 0:
            address = 0x00;
            break;
        case 1:
            address = 0x40;
            break;
        default:
            address = 0x00;
    }
    address += column;
    LCD_Send_cmd(0x80 | address, hi2c1);
}

/**
 * @brief Clear the LCD
 * @param hi2c1 Pointer to the I2C handle
 */
void LCD_Clear(I2C_HandleTypeDef *hi2c1)
{
    LCD_Set_cursor(0, 0, hi2c1);
    LCD_Write_string("                ", hi2c1);
    LCD_Set_cursor(1, 0, hi2c1);
    LCD_Write_string("                ", hi2c1);
}

/**
 * @brief Display data on the LCD for a specific menu state
 * @param zadany_kat The set angle value
 * @param odczytany_kat The measured angle value
 * @param hmen Pointer to the MenuHandle
 */
void LCD_Display(float zadany_kat, float odczytany_kat, MenuHandle* hmen)
{
    char linijka_zadana[17];
    char linijka_aktualna[17];
    if (hmen->state == _DEBUG)
    {
        sprintf(linijka_zadana, "SET  DEBUG   GET");
    }
    else if (hmen->state == _MANUAL)
    {
        sprintf(linijka_zadana, "SET  MANUAL  GET");
    }
    else if (hmen->state == _REMOTE)
    {
        sprintf(linijka_zadana, "SET  REMOTE  GET");
    }
    else {
        sprintf(linijka_zadana,"%s", "SET   IDLE   GET");
    }

    int lenght2 = sprintf(linijka_aktualna, "%06.2f*  %06.2f*", zadany_kat, odczytany_kat);
    linijka_aktualna[lenght2-1] = 223;
    linijka_aktualna[6] = 223;

    LCD_Set_cursor(0, 0, &hi2c1);
    LCD_Write_string(linijka_zadana, &hi2c1);
    LCD_Set_cursor(1, 0, &hi2c1);
    LCD_Write_string(linijka_aktualna, &hi2c1);
}
