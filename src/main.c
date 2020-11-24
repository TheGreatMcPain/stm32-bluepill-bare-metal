#include "main.h"

int main() {
  sysclock_init();
  systick_init();

  // Initialize GPIO Port C Pin 8
  // Mode Output Push-Pull at 2Mhz
  gpio_init(PC, 8, OUT2, O_GP_PP);

  while (1) {
    toggle_gpio(PC, 8);

    DelayMS(1000);
  }
}
