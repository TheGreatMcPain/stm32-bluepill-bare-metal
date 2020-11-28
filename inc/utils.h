#ifndef __SYSCLOCK_H
#define __SYSCLOCK_H
#include "stdint.h"
#define RCC_CR (*(volatile uint32_t *)0x40021000UL)
#define RCC_CFGR (*(volatile uint32_t *)0x40021004UL)

#define STK_CTRL (*(volatile uint32_t *)0xE000E010UL)
#define STK_LOAD (*(volatile uint32_t *)0xE000E014UL)
#define STK_VAL (*(volatile uint32_t *)0xE000E018UL)

void sysclock_init(void);     // Set up clock speed
void systick_init(void);      // Setup SysTick counter.
void tim4_tick_init(void);    // Setup TIM4 as tick counter.
uint32_t getTickMillis(void); // Get tick count from TIM4 counter.
void DelayMS(uint32_t t);     // Delay for num of milli-seconds.
#endif
