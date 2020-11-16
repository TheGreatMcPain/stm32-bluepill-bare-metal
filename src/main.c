#include "stm32f100xb.h"

void dumbDelay(int value);

int main() {
  RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;

  GPIOC->CRH &= ~GPIO_CRH_CNF8;
  GPIOC->CRH |= GPIO_CRH_MODE8_1;

  while (1) {
    GPIOC->ODR ^= (1 << 8);
    dumbDelay(1000000000);
  }
}

void dumbDelay(int value) {
  while (value > 0) {
    value--;
  }
}
