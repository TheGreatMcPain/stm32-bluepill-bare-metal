#include "i2c_driver.h"

// void i2c_read() {
//  // Don't need this yet, and I don't know how to test it.
//}

void i2c_write(I2C_TypeDef *I2C, uint8_t devaddr, uint8_t memaddr,
               uint8_t *data, uint8_t length) {
  uint32_t temp = 0;

  // Generate start condition
  I2C->CR1 |= I2C_CR1_START;

  while (!(I2C->SR1 & I2C_SR1_SB)) {
    // Wait for start condition
  }

  I2C->DR = devaddr; // write device address

  while (!(I2C->SR1 & I2C_SR1_ADDR)) {
    // Wait for ADDR sent
  }
  temp = I2C->SR2; // Clear ADDR flag by reading SR2

  I2C->DR = memaddr; // Address to write to

  while (!(I2C->SR1 & I2C_SR1_TXE)) {
    // Wait for DR to empty
  }

  // Write data.
  for (temp = 0; temp < length; temp++) {
    I2C->DR = data[temp]; // Send some data

    while (!(I2C->SR1 & I2C_SR1_TXE)) {
      // Wait for DR to empty
    }
  }

  I2C->CR1 |= I2C_CR1_STOP; // Stop after start condition.
}

void i2c_init(I2C_TypeDef *I2C, uint8_t speed) {
  RCC->APB2ENR |= 1; // Enable Alternative function

  if (I2C == I2C1) {
    // Enable GPIOB pins 6 and 7 Alternate function Open-Drain
    gpio_init(GPIOB, 6, OUT50, O_AF_OD);
    gpio_init(GPIOB, 7, OUT50, O_AF_OD);
    RCC->APB1ENR |= RCC_APB1ENR_I2C1EN; // Enable I2C1
  } else if (I2C == I2C2) {
    // Enable GPIO  pins 10 and 11 Alternate function Open-Drain
    gpio_init(GPIOB, 10, OUT50, O_AF_OD);
    gpio_init(GPIOB, 11, OUT50, O_AF_OD);
    RCC->APB1ENR |= RCC_APB1ENR_I2C2EN; // Enable I2C2
  }

  // Ensure I2C is reset.
  I2C->CR1 |= I2C_CR1_SWRST;
  I2C->CR1 &= ~(I2C_CR1_SWRST);

  I2C->CR2 = getPCLK1Freq() / 1000000; // Freq value of APB1 buss

  // Set speed mode
  I2C->CCR = speed;

  I2C->TRISE = 25;

  // Enable ACK bit
  I2C->CR1 |= I2C_CR1_ACK;

  // Finally enable the Peripheral
  I2C->CR1 |= I2C_CR1_PE;
}
