/*
 * Based on controllerstech's LCD2004 I2C driver.
 */
#ifndef __I2C_LCD_DRIVER_H
#define __I2C_LCD_DRIVER_H
#include "i2c_driver.h"
#include "stdint.h"
#include "sysclock.h"

void lcd_send_cmd(uint8_t i2c, char cmd);

void lcd_send_data(uint8_t i2c, char data);

void lcd_clear(uint8_t i2c);

void lcd_put_cur(uint8_t i2c, int row, int col);

void lcd_init(uint8_t i2c);

void lcd_send_string(uint8_t i2c, char *str);
#endif
