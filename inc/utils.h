#ifndef __SYSCLOCK_H
#define __SYSCLOCK_H
#include "stdint.h"
#include "stm32f1xx.h"

void sysclock_init(void);     // Set up clock speed
void systick_init(void);      // Setup SysTick counter.
void tim4_tick_init(void);    // Setup TIM4 as tick counter.
uint32_t getTickMillis(void); // Get tick count from TIM4 counter.
void DelayMS(uint32_t t);     // Delay for num of milli-seconds.
#endif
