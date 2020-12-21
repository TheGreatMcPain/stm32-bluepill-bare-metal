#include "main.h"

int main() {
  sysclock_init();
  systick_init();
  tim4_tick_init();

  gpio_init(GPIOC, 13, OUT50, O_GP_PP);
  gpio_init(GPIOA, 12, OUT50, O_GP_PP);

  while (1) {
    toggle_gpio(GPIOC, 13);
    DelayMS(500);
    toggle_gpio(GPIOA, 12);
    DelayMS(500);
  }
}
