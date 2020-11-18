#ifndef __GPIO_DRIVER_H
#define __GPIO_DRIVER_H
#include "stdint.h"

#define RCC_APB2ENR (*(volatile uint32_t *)0x40021018UL)

#define GPIO_A (*(volatile uint32_t *)0x40010800UL)
#define GPIO_B (*(volatile uint32_t *)0x40010C00UL)
#define GPIO_C (*(volatile uint32_t *)0x40011000UL)
#define GPIO_D (*(volatile uint32_t *)0x40011400UL)
#define GPIO_E (*(volatile uint32_t *)0x40011800UL)

// GPIO Port list
#define PA 1
#define PB 2
#define PC 3
#define PD 4
#define PE 5

// GPIO Directions
#define IN 0
#define OUT10 1
#define OUT2 2
#define OUT50 3

// GPIO Input options
#define I_AN 0
#define I_F 1
#define I_PP 2

// GPIO Output options
#define O_GP_PP 0
#define O_GP_OD 1
#define O_AF_PP 2
#define O_AF_OD 3

// States
#define LOW 0
#define HIGH 1

void gpio_init(uint8_t port, uint8_t pin, uint8_t direction, uint8_t option);

int read_gpio(uint8_t port, uint8_t pin);

void write_gpio(uint8_t port, uint8_t pin, uint8_t state);

void toggle_gpio(uint8_t port, uint8_t pin);
#endif
