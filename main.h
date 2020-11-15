#ifndef __MAIN_H
#define __MAIN_H

#include <stdint.h>

#define RCC (0x40021000UL)
#define RCC_APB2ENR (*(volatile uint32_t *)(RCC + 0x018UL))

#define GPIOA (0x40010800UL)
#define GPIOC (0x40011000UL)

#define GPIOA_CRL (*(volatile uint32_t *)(GPIOA))
#define GPIOC_CRH (*(volatile uint32_t *)(GPIOC + 0x04))

#define GPIOA_IDR (*(volatile uint32_t *)(GPIOA + 0x08))
#define GPIOC_ODR (*(volatile uint32_t *)(GPIOC + 0x0C))

#endif
