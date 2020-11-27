#include "i2c_driver.h"

// void i2c_read() {
//  // Don't need this yet, and I don't know how to test it.
//}

void i2c_write(uint8_t i2c, uint8_t devaddr, uint8_t memaddr, uint8_t *data,
               uint8_t length) {
  uint32_t temp = 0;

  if (i2c == 1) {
    // Generate start condition
    I2C1->CR1 |= (1 << 8);

    while (!(I2C1->SR1 & 1)) {
      // Wait for start condition
    }

    I2C1->DR = devaddr; // write device address

    while (!(I2C1->SR1 & 2)) {
      // Wait for ADDR sent
    }
    temp = I2C1->SR2; // Clear ADDR flag by reading SR2

    I2C1->DR = memaddr; // Address to write to

    while (!(I2C1->SR1 & (1 << 7))) {
      // Wait for DR to empty
    }

    // Write data.
    for (temp = 0; temp < length; temp++) {
      I2C1->DR = data[temp]; // Send some data

      while (!(I2C1->SR1 & (1 << 7))) {
        // Wait for DR to empty
      }
    }

    I2C1->CR1 |= (1 << 9); // Stop after start condition.
  } else if (i2c == 2) {
    // Generate start condition
    I2C2->CR1 |= (1 << 8);

    while (!(I2C2->SR1 & 1)) {
      // Wait for start condition
    }

    I2C2->DR = devaddr; // write device address

    while (!(I2C2->SR1 & 2)) {
      // Wait for ADDR sent
    }
    temp = I2C2->SR2; // Clear ADDR flag by reading SR2

    I2C2->DR = memaddr; // Address to write to

    while (!(I2C2->SR1 & (1 << 7))) {
      // Wait for DR to empty
    }

    // Write data.
    for (temp = 0; temp < length; temp++) {
      I2C2->DR = data[temp]; // Send some data

      while (!(I2C2->SR1 & (1 << 7))) {
        // Wait for DR to empty
      }
    }

    I2C2->CR1 |= (1 << 9); // Stop after start condition.
  }
}

void i2c_init(uint8_t i2c, uint8_t speed) {
  RCC->APB2ENR |= 1; // Enable Alternative function

  if (i2c == 1) {
    // Enable GPIOB pins 6 and 7 Alternate function Open-Drain
    gpio_init(PB, 6, OUT50, O_AF_OD);
    gpio_init(PB, 7, OUT50, O_AF_OD);
    RCC->APB1ENR |= (1 << 21); // Enable I2C1

    I2C1->CR2 = 24; // Freq value of APB1 buss = 24

    // Set speed mode
    I2C1->CCR = speed;

    I2C1->TRISE = 25;

    // Enable ACK bit
    I2C1->CR1 |= (10 << 1);

    // Finally enable the Peripheral
    I2C1->CR1 |= 1;
  } else if (i2c == 2) {
    // Enable GPIO
    gpio_init(PB, 10, OUT50, O_AF_OD);
    gpio_init(PB, 11, OUT50, O_AF_OD);
    RCC->APB1ENR |= (1 << 22); // Enable I2C2

    I2C2->CR2 = 24; // Freq value of APB1 buss = 24

    // Set speed mode
    I2C2->CCR = speed;

    I2C2->TRISE = 25;

    // Enable ACK bit
    I2C2->CR1 |= (10 << 1);

    // Finally enable the Peripheral
    I2C2->CR1 |= 1;
  }
}
