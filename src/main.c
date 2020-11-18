#include "main.h"

int main() {
  sysclock_init();

  // Initialize GPIO Port C Pin 8
  // Mode Output Push-Pull at 2Mhz
  gpio_init(PC, 8, OUT2, O_GP_PP);

  // Initialize GPIO Port A Pin 0
  // Mode Input Pull-Pull
  gpio_init(PA, 0, IN, I_PP);

  while (1) {
    while (!read_gpio(PA, 0)) {
      // Wait for button
    }

    toggle_gpio(PC, 8); // Toggle LED

    while (read_gpio(PA, 0)) {
      // Wait for Button to release.
    }
  }
}
