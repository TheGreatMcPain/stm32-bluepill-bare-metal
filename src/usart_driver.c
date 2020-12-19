#include "usart_driver.h"
#include "string.h"

void usart_init(USART_TypeDef *USART) {
  // Enable alternate function.
  RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;

  if (USART == USART1) {
    // Setup GPIO's and enable USART Clock.
    gpio_init(GPIOA, 9, OUT50, O_AF_PP); // TX Pin
    gpio_init(GPIOA, 10, IN, I_F);       // RX Pin
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
  } else if (USART == USART2) {
    gpio_init(GPIOA, 2, OUT50, O_AF_PP);
    gpio_init(GPIOA, 3, IN, I_F);
    RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
  } else if (USART == USART3) {
    gpio_init(GPIOB, 10, OUT50, O_AF_PP);
    gpio_init(GPIOB, 11, IN, I_F);
    RCC->APB1ENR |= RCC_APB1ENR_USART3EN;
  }

  // Configure Baud-Rate
  // (The STM32VLDiscovery board uses a Max 24Mhz on all clocks.)
  uint16_t usartdiv = SystemCoreClock / 115200;
  USART->BRR = (((usartdiv / 16) << USART_BRR_DIV_Mantissa_Pos) |
                ((usartdiv % 16) << USART_BRR_DIV_Fraction_Pos));

  // Enable USART, transmit, and receive.
  USART->CR1 |= (USART_CR1_UE | USART_CR1_TE | USART_CR1_RE);
}

void usart_send_string(USART_TypeDef *USART, char *str, uint32_t size) {
  uint32_t count = size;

  while (count--) {
    while (!(USART->SR & USART_SR_TXE)) {
    }
    USART->DR = *str++;
  }
}

// Receive characters and send them back.
void usart_echo(USART_TypeDef *USART) {
  uint8_t rxb = '\0';

  while (!(USART->SR & USART_SR_RXNE)) {
    // Wait for a byte of data to arrive.
  }
  rxb = USART->DR;

  while (!(USART->SR & USART_SR_TXE)) {
    // Wait for transmit registor to empty.
  }

  USART->DR = rxb;
}
