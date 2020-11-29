/*
 * Based on controllerstech's LCD2004 I2C driver.
 */
#ifndef __I2C_LCD_DRIVER_H
#define __I2C_LCD_DRIVER_H
#include "i2c_driver.h"
#include "stdint.h"
#include "utils.h"

void lcd_send_cmd(I2C_TypeDef *I2C, char cmd);

void lcd_send_data(I2C_TypeDef *I2C, char data);

void lcd_clear(I2C_TypeDef *I2C);

void lcd_put_cur(I2C_TypeDef *I2C, int row, int col);

void lcd_init(I2C_TypeDef *I2C);

void lcd_send_string(I2C_TypeDef *I2C, char *str);
#endif
