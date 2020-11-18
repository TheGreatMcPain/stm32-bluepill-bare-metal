#ifndef __SYSCLOCK_H
#define __SYSCLOCK_H
#include "stdint.h"
#define RCC_CR (*(volatile uint32_t *)0x40021000UL)
#define RCC_CFGR (*(volatile uint32_t *)0x40021004UL)

#define STK_CTRL (*(volatile uint32_t *)0xE000E010UL)
#define STK_LOAD (*(volatile uint32_t *)0xE000E014UL)
#define STK_VAL (*(volatile uint32_t *)0xE000E018UL)

void sysclock_init(void);
void DelayMS(unsigned long t);
#endif
