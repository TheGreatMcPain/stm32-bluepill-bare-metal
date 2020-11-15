#include "main.h"

#define BUTTON_PIN (0)
#define LED_PIN (8)

void dummyDelay(volatile int delay);

int main(void) {
  RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
  RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;

  /* GPIOA pin 0 in input mode */
  GPIOA->CRL &= ~(3 << 2); // Reset to analog
  GPIOA->CRL |= (2 << 2);  // Input with pull-up / pull-down
  GPIOA->CRL &= ~(3 << 0); // Input mode

  /* GPIOC pin 8 in push-pull mode */
  GPIOC->CRH &= ~(1 << 2); // Output push-pull
  GPIOC->CRH |= (1 << 1);  // Output mode 2 Mhz

  uint8_t button_down = 0;

  while (1) {
    uint32_t idr_val = ~GPIOA->IDR;

    if (idr_val & (1 << BUTTON_PIN)) {
      if (!button_down) {
        GPIOC->ODR ^= (1 << LED_PIN);
      }
      button_down = 1;
    } else {
      button_down = 0;
    }
  }
}

void dummyDelay(int delay) {
  while (delay-- > 0) {
    ;
  }
}
