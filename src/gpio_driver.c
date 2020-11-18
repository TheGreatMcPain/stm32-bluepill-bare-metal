#include "gpio_driver.h"

void gpio_init(uint8_t port, uint8_t pin, uint8_t direction, uint8_t option) {
  volatile uint32_t *CR = 0; // Init to 0 to supress warning
  uint8_t tPIN = pin;
  uint8_t offset = 0x00;

  if (pin > 7) {
    tPIN -= 8;
    offset = 0x01;
  }

  switch (port) {
  case 1:
    RCC_APB2ENR |= (1 << 2); // Enable port A
    CR = (volatile uint32_t *)(&GPIO_A + offset);
    break;
  case 2:
    RCC_APB2ENR |= (1 << 3); // Enable port B
    CR = (volatile uint32_t *)(&GPIO_B + offset);
    break;
  case 3:
    RCC_APB2ENR |= (1 << 4); // Enable port C
    CR = (volatile uint32_t *)(&GPIO_C + offset);
    break;
  case 4:
    RCC_APB2ENR |= (1 << 5); // Enable port D
    CR = (volatile uint32_t *)(&GPIO_D + offset);
    break;
  case 5:
    RCC_APB2ENR |= (1 << 6); // Enable port E
    CR = (volatile uint32_t *)(&GPIO_E + offset);
    break;
  }

  *CR &= ~(0xF << (tPIN)*4); // Reset the target pin
  // Set up the direction and the option of the PIN
  *CR |= ((direction << (tPIN * 4)) | (option << (tPIN * 4 + 2)));
}

int read_gpio(uint8_t port, uint8_t pin) {
  volatile uint32_t *IDR = 0;
  uint8_t offset = 0x02;

  // Get the IDR register of a GPIO port
  switch (port) {
  case 1:
    IDR = (volatile uint32_t *)(&GPIO_A + offset);
    break;
  case 2:
    IDR = (volatile uint32_t *)(&GPIO_B + offset);
    break;
  case 3:
    IDR = (volatile uint32_t *)(&GPIO_C + offset);
    break;
  case 4:
    IDR = (volatile uint32_t *)(&GPIO_D + offset);
    break;
  case 5:
    IDR = (volatile uint32_t *)(&GPIO_E + offset);
    break;
  }

  // Return the value of the PIN's IDR
  return ((*IDR & (1 << pin)) >> pin);
}

void write_gpio(uint8_t port, uint8_t pin, uint8_t state) {
  volatile uint32_t *ODR = 0;
  uint8_t offset = 0x03;

  // Get the ODR register of a GPIO port
  switch (port) {
  case 1:
    ODR = (volatile uint32_t *)(&GPIO_A + offset);
    break;
  case 2:
    ODR = (volatile uint32_t *)(&GPIO_B + offset);
    break;
  case 3:
    ODR = (volatile uint32_t *)(&GPIO_C + offset);
    break;
  case 4:
    ODR = (volatile uint32_t *)(&GPIO_D + offset);
    break;
  case 5:
    ODR = (volatile uint32_t *)(&GPIO_E + offset);
    break;
  }

  // Set the state of the PIN's ODR
  state ? (*ODR |= (state << pin)) : (*ODR &= ~(1 << pin));
}

void toggle_gpio(uint8_t port, uint8_t pin) {
  if (read_gpio(port, pin)) {
    write_gpio(port, pin, 0);
  } else {
    write_gpio(port, pin, 1);
  }
}
