#ifndef __I2C_DRIVER_H
#define __I2C_DRIVER_H
#include "gpio_driver.h"
#include "stdint.h"
#include "stm32f1xx.h"
extern uint32_t SystemCoreClock;

// Std mode: 100Khz = 100000
// Fst mode: 400Khz = 400000
//
// Maximum PCLK = 24000000 on STM32VLDiscovery
#define i2c_SM (((1.0 / 100000.0) / 2.0) / (1.0 / (float)SystemCoreClock))
#define i2c_FM (((1.0 / 400000.0) / 2.0) / (1.0 / (float)SystemCoreClock))

// void i2c_read();

void i2c_write(I2C_TypeDef *I2C, uint8_t devaddr, uint8_t memaddr,
               uint8_t *data, uint8_t length);

void i2c_init(I2C_TypeDef *I2C, uint8_t speed);
#endif
