#include "main.h"

int main() {
  systick_init();

  RCC->APB2ENR |= RCC_APB2ENR_IOPCEN; // Enable GPIOC

  GPIOC->CRH &= ~GPIO_CRH_CNF8;   // Out push-pull
  GPIOC->CRH |= GPIO_CRH_MODE8_1; // Output 2Mhz

  while (1) {
    GPIOC->ODR ^= (1 << 8); // Toggle LED
    DelayMS(1000);          // Delay for 1 second
  }
}
