#include "main.h"

static const int led1_delay = 1000;
static const int led2_delay = 500;

struct led_args {
  int led_num;
  int led_delay;
};

static void led_task(void *args) {
  int led_num = ((struct led_args *)args)->led_num;
  int ms_delay = ((struct led_args *)args)->led_delay;

  while (1) {
    if (led_num == 1) {
      toggle_gpio(PC, 8);
    } else if (led_num == 2) {
      toggle_gpio(PC, 9);
    }

    vTaskDelay(pdMS_TO_TICKS(ms_delay));
  }
}

int main() {
  sysclock_init();
  systick_init();

  // Initialize GPIO Port C Pin 8
  // Mode Output Push-Pull at 2Mhz
  gpio_init(PC, 8, OUT2, O_GP_PP);
  gpio_init(PC, 9, OUT2, O_GP_PP);

  int *led1Ptr = (int *)malloc(sizeof(int));

  *led1Ptr = 1;

  struct led_args *led1ArgsPtr =
      (struct led_args *)malloc(sizeof(struct led_args));

  struct led_args *led2ArgsPtr =
      (struct led_args *)malloc(sizeof(struct led_args));

  led1ArgsPtr->led_num = 1;
  led1ArgsPtr->led_delay = led1_delay;

  led2ArgsPtr->led_num = 2;
  led2ArgsPtr->led_delay = led2_delay;

  xTaskCreate(led_task, "LED_Blink_1", 128, (void *)led1ArgsPtr,
              configMAX_PRIORITIES - 1, NULL);

  xTaskCreate(led_task, "LED_Blink_2", 128, (void *)led2ArgsPtr,
              configMAX_PRIORITIES - 1, NULL);

  vTaskStartScheduler();
}
