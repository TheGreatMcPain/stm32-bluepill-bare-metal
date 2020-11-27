#ifndef __I2C_DRIVER_H
#define __I2C_DRIVER_H
#include "gpio_driver.h"
#include "stdint.h"
#include "stm32f1xx.h"

// 1/24Mhz = 41.6nS
// Std mode: 100Khz
// Fst mode: 500Khz
// 1/100Khz = 10uS then divide by 2. 10uS/2 = 5uS
// 5uS / 41.6nS = 120
//
// 1/500Khz = 2uS, 2/16 = 0.125
// 1.25 / 41.6 = 30
#define i2c_SM 120
#define i2c_FM 30

// void i2c_read();

void i2c_write(uint8_t i2c, uint8_t devaddr, uint8_t memaddr, uint8_t *data,
               uint8_t length);

void i2c_init(uint8_t i2c, uint8_t speed);
#endif
