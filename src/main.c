#include "main.h"
#include "i2c_driver.h"
#include "i2c_lcd_driver.h"

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

static void lcd_shift_task(void *args) {
  uint8_t i2c = *(int *)args;
  uint8_t pos = 0;

  while (1) {
    for (pos = 0; pos < 6; pos++) {
      lcd_send_cmd(i2c, 0x1C); // shift to the right.
      vTaskDelay(pdMS_TO_TICKS(350));
    }

    for (pos = 0; pos < 6; pos++) {
      lcd_send_cmd(i2c, 0x18); // shift to the left.
      vTaskDelay(pdMS_TO_TICKS(350));
    }
  }
}

int main() {
  sysclock_init();
  systick_init();

  // Initialize I2C2
  i2c_init(2, i2c_SM);
  // Init LCD on I2C2
  lcd_init(2);

  // Write hello world to LCD
  lcd_put_cur(2, 0, 2);
  lcd_send_string(2, "HelloWorld");
  lcd_put_cur(2, 1, 1);
  lcd_send_string(2, "LCD20x4 Demo");
  lcd_put_cur(2, 2, 6);
  lcd_send_string(2, "BY");
  lcd_put_cur(2, 3, 0);
  lcd_send_string(2, "TheGreatMcPain");

  // Initialize GPIO Port C Pin 8
  // Mode Output Push-Pull at 50Mhz
  gpio_init(PC, 8, OUT50, O_GP_PP);
  gpio_init(PC, 9, OUT50, O_GP_PP);

  int *led1Ptr = (int *)malloc(sizeof(int));

  *led1Ptr = 1;

  struct led_args *led1ArgsPtr =
      (struct led_args *)malloc(sizeof(struct led_args));

  struct led_args *led2ArgsPtr =
      (struct led_args *)malloc(sizeof(struct led_args));

  led1ArgsPtr->led_num = 1;
  led1ArgsPtr->led_delay = 1000;

  led2ArgsPtr->led_num = 2;
  led2ArgsPtr->led_delay = 500;

  int *i2cPtr = (int *)malloc(sizeof(int));
  *i2cPtr = 2;

  xTaskCreate(lcd_shift_task, "LCD_Shift", 128, (void *)i2cPtr,
              configMAX_PRIORITIES - 1, NULL);

  xTaskCreate(led_task, "LED_Blink_1", 128, (void *)led1ArgsPtr,
              configMAX_PRIORITIES - 1, NULL);

  xTaskCreate(led_task, "LED_Blink_2", 128, (void *)led2ArgsPtr,
              configMAX_PRIORITIES - 1, NULL);

  vTaskStartScheduler();
}
