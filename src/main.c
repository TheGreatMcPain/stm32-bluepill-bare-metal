// #include "FreeRTOS.h"
#include "gpio_driver.h"
// #include "i2c_driver.h"
// #include "i2c_lcd_driver.h"
// #include "max6675_driver.h"
// #include "spi_driver.h"
#include "stm32f1xx.h"
// #include "task.h"
#include "usart_driver.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

volatile uint16_t val = 0;

int main() {
  sysclock_init();
  systick_init();
  tim4_tick_init();
  char string[80] = "\0";

  usart_init(USART1, 115200);

  RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
  RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
  EXTI->IMR |= EXTI_IMR_IM1;
  EXTI->IMR |= EXTI_IMR_IM0;
  NVIC_EnableIRQ(EXTI1_IRQn);
  NVIC_EnableIRQ(EXTI0_IRQn);
  EXTI->RTSR |= EXTI_RTSR_RT1;
  EXTI->FTSR |= EXTI_FTSR_FT0;
  AFIO->EXTICR[0] |= AFIO_EXTICR1_EXTI1_PB;
  AFIO->EXTICR[0] |= AFIO_EXTICR1_EXTI0_PB;

  while (1) {
    sprintf(string, "%d: Encoder Val\n\r", val);
    usart_send_string(USART1, string, 80);
    DelayMS(10);
  }
}

void EXTI1_IRQHandler(void) {
  EXTI->PR |= 1 << 1;
  if (read_gpio(GPIOB, 0)) {
    val++;
  } else {
    val--;
  }
}

void EXTI0_IRQHandler(void) {
  EXTI->PR |= 1 << 1;
  if (read_gpio(GPIOB, 1)) {
    val++;
  } else {
    val--;
  }
}
