#include "main.h"

#define BUTTON_PIN (0)
#define LED_PIN (8)

void dummyDelay(int delay);

int main(void) {
  RCC_APB2ENR |= (1 << 4); // Enable GPIOC
  RCC_APB2ENR |= (1 << 2); // Enable GPIOA

  /* GPIOA pin 0 in input mode */
  GPIOA_CRL &= ~(3 << 2); // Mask
  GPIOA_CRL |= (2 << 2);  // Input with pull-up / pull-down
  GPIOA_CRL &= ~(3 << 0); // Input mode

  /* GPIOC pin 8 in push-pull mode */
  GPIOC_CRH &= ~(1 << 2); // Output push-pull
  GPIOC_CRH |= (1 << 1);  // Output mode 2 Mhz

  uint8_t button_down = 0;

  while (1) {
    uint32_t idr_val = ~GPIOA_IDR;

    if (idr_val & (1 << BUTTON_PIN)) {
      if (!button_down) {
        GPIOC_ODR ^= (1 << LED_PIN);
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
