#ifndef __SYSCLOCK_H
#define __SYSCLOCK_H
#include "stm32f1xx.h"

void systick_init(void);
void DelayMS(unsigned long t);
#endif
