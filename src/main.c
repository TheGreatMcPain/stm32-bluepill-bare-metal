#include "main.h"

#define STRING_SIZE 18

int main() {
  uint32_t counter = 0;

  sysclock_init();
  systick_init();
  tim4_tick_init();

  usart_init(USART1);

  gpio_init(GPIOC, 8, OUT50, O_GP_PP);

  while (1) {
    char test[STRING_SIZE] = "\0";
    counter++;

    toggle_gpio(GPIOC, 8);

    if (read_gpio(GPIOC, 8)) {
      sprintf(test, "%03d: LED is ON\r\n", (int)counter);
    } else {
      sprintf(test, "%03d: LED is OFF\r\n", (int)counter);
    }

    usart_send_string(USART1, test, STRING_SIZE);

    DelayMS(1000);
  }
}
