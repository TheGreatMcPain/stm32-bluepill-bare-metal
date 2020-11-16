#include "sysclock.h"

void systick_init(void) {
  /* Configure the HCLK to run at 24Mhz */
  RCC->CR |= RCC_CR_HSEON; // Turn on External crystal

  while (!(RCC->CR & RCC_CR_HSERDY)) {
    // Wait for HSE to be stable
  }

  // Configure PLL while it is off
  RCC->CFGR &= ~(RCC_CFGR_PLLSRC | RCC_CFGR_PLLXTPRE | RCC_CFGR_PLLMULL);

  RCC->CFGR &= ~(RCC_CFGR_PLLXTPRE); // PLLXTPRE to 0
  RCC->CFGR |= RCC_CFGR_PLLSRC;      // PLL Source
  RCC->CFGR |= RCC_CFGR_PLLMULL3;    // PLL Multiplier
  RCC->CFGR |= RCC_CFGR_HPRE_DIV1;   // AHB Prescaler
  RCC->CFGR |= RCC_CFGR_PPRE1_DIV1;  // APB1 prescaler
  RCC->CFGR |= RCC_CFGR_PPRE2_DIV1;  // APB2 prescaler

  RCC->CR |= RCC_CR_PLLON; // Turn on the PLL

  while (!(RCC->CR & RCC_CR_PLLRDY)) {
    // Wait till PLL is ready
  }

  // Use PLL as SysClock Source
  RCC->CFGR &= ~(RCC_CFGR_SW);
  RCC->CFGR |= RCC_CFGR_SW_PLL;
  while (!(RCC->CFGR & RCC_CFGR_SWS_PLL)) {
    // Wait for System Clock to switch to PLL
  }

  // Update SystemCoreClock variable
  SystemCoreClockUpdate();

  /* Configure SysTick Counter */
  SysTick->CTRL = 0;
  SysTick->LOAD = 0x00FFFFFF;
  SysTick->VAL = 0;

  SysTick->CTRL = 5;
}

void millisDelay(void) {
  // Set the counter limit to a millisecond
  SysTick->LOAD = (SystemCoreClock / 1000) - 1;
  // Reset the SysTick value register
  SysTick->VAL = 0;

  // Wait for the counter to wrap back to zero.
  while ((SysTick->CTRL & (1 << 16)) == 0) {
  }
}

void DelayMS(unsigned long t) {
  for (; t > 0; t--) {
    millisDelay();
  }
}
