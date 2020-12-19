#ifndef __USART_DRIVER_H
#define __USART_DRIVER_H
#include "gpio_driver.h"
#include "stm32f1xx.h"

// Setup USART with baud-rate of 9600
void usart_init(USART_TypeDef *USART);

// Send a string over USART
void usart_send_string(USART_TypeDef *USART, char *str, uint32_t size);

// Echo test function
void usart_echo(USART_TypeDef *USART);
#endif
