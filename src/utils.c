#include "utils.h"
#include "stm32f1xx.h"

volatile uint32_t tickCounter = 0;

// Set clock speed to 24Mhz and Enable SysTick Counter
void sysclock_init(void) {
  /* Configure the HCLK to run at 24Mhz */
  RCC_CR |= (1 << 16); // Enable HSEON bit

  while (!(RCC_CR & (1 << 17))) {
    // Wait for HSERDY bit to flip to 1.
  }

  // Configure PLL while it is off
  // Reset PLLSRC, PLLXTPRE, and PLLMUL
  RCC_CFGR &= ~((1 << 16) | (1 << 17) | (16 << 18));

  RCC_CFGR &= ~(1 << 17); // PLLXTPRE bit to 0
  RCC_CFGR |= (1 << 16);  // PLLSRC bit to 1
  RCC_CFGR |= (1 << 18);  // PLLMULL bit to 0001
  RCC_CFGR |= (0 << 4);   // HPRE to 0 aka SYSCLK no division.
  RCC_CFGR |= (0 << 8);   // PPRE1 to 0 aka HCLK APB1 not divided.
  RCC_CFGR |= (0 << 11);  // PPRE2 to 0 aka HCLK APB2 not divided.

  RCC_CR |= (1 << 24); // Enable PLLON bit

  while (!(RCC_CR & (1 << 25))) {
    // Wait till PLLRDY bit to flip to 1
  }

  // Use PLL as SysClock Source
  // RCC->CFGR &= ~(RCC_CFGR_SW);
  RCC_CFGR &= ~(3); // Reset SW bits to 0b11
  // RCC->CFGR |= RCC_CFGR_SW_PLL;
  RCC_CFGR |= 2; // SW bit to PLL
  while (!(RCC_CFGR & (2 << 2))) {
    // Wait for SWS bits to change to 2, aka PLL
  }
}

// Use TIM4 as tick source
void tim4_tick_init(void) {
  // Enable TIM4
  RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;

  // Enable global interrupt for TIM4
  NVIC_SetPriority(TIM4_IRQn, 0x03);
  NVIC_EnableIRQ(TIM4_IRQn);

  // Make sure TIM4 counter is off
  TIM4->CR1 &= ~(TIM_CR1_CEN);

  // Reset the peripheral.
  RCC->APB1RSTR |= (RCC_APB1RSTR_TIM4RST);
  RCC->APB1RSTR &= ~(RCC_APB1RSTR_TIM4RST);

  // Set prescaler/autoreload timing registers
  TIM4->PSC = 23;  // 24Mhz
  TIM4->ARR = 999; // 1Mhz = 1ms

  // Send an update event to reset the timer and apply settings.
  TIM4->EGR |= TIM_EGR_UG;

  // Enable the hardware interrupt.
  TIM4->DIER |= TIM_DIER_UIE;

  // Enable the timer.
  TIM4->CR1 |= TIM_CR1_CEN;
}

void systick_init(void) {
  /* Configure SysTick Counter */
  STK_CTRL = 0;          // Reset CTRL
  STK_LOAD = 0x00FFFFFF; // Set LOAD to Max value
  STK_VAL = 0;           // Reset VAL

  STK_CTRL = 5; // Set CLKSOURCE to AHB, Disable TICKINT, and ENABLE Counter
}

void millisDelay(void) {
  // Set the counter limit to a millisecond

  // I set the clock speed to 24Mhz
  STK_LOAD = 24000 - 1;
  // Reset the SysTick value register
  STK_VAL = 0;

  // Wait for the counter to wrap back to zero.
  while ((STK_CTRL & (1 << 16)) == 0) {
  }
}

// void DelayMS(uint32_t t) {
//   for (; t > 0; t--) {
//     millisDelay();
//   }
// }

uint32_t getTickMillis(void) { return tickCounter; }

void DelayMS(uint32_t t) {
  uint32_t currentTick = tickCounter;

  while (tickCounter - currentTick == t) {
    // Wait for t number of ticks.
  }
}

void TIM4_IRQHandler(void) {
  if (TIM4->SR & TIM_SR_UIF) {
    TIM4->SR &= ~(TIM_SR_UIF);
    // Increment tickCounter
    tickCounter++;
  }
}
