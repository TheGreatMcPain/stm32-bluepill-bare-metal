#include "stm32f100xb.h"

void dumbDelay(int value);

int main() {
  RCC->APB2ENR |= RCC_APB2ENR_IOPCEN; // Enable GPIOC

  GPIOC->CRH &= ~GPIO_CRH_CNF8;   // Out push-pull
  GPIOC->CRH |= GPIO_CRH_MODE8_1; // Output 2Mhz

  while (1) {
    GPIOC->ODR ^= (1 << 8); // Toggle LED
    dumbDelay(1000000);     // Dump Delay
  }
}

void dumbDelay(int value) {
  while (value > 0) {
    value--;
  }
}
