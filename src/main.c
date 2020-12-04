#include "main.h"
#define LCD_I2C I2C2
#define MAX_SPI SPI1

int main() {
  char lcdString[20];
  float temp = 0;

  sysclock_init();
  systick_init();
  tim4_tick_init();

  // Initialize I2C2
  i2c_init(LCD_I2C, i2c_SM);

  // Initialize SPI1
  spi_init(MAX_SPI);

  // Initialize GPIOA PIN 7
  gpio_init(GPIOA, 4, OUT50, O_GP_PP);
  write_gpio(GPIOA, 4, HIGH);
  // write_gpio(GPIOA, 7, LOW);

  gpio_init(GPIOC, 8, OUT50, O_GP_PP);

  // Init LCD on I2C2
  lcd_init(LCD_I2C);

  // Test LCD
  lcd_put_cur(LCD_I2C, 0, 0);
  lcd_send_string(LCD_I2C, "Hello World!");

  while (1) {
    temp = max5575_read_temp(MAX_SPI, GPIOA, 4, TEMP_F);

    sprintf(lcdString, "Temp: %02d.%02d", (int)temp,
            (int)((temp - (int)temp) * 100));

    lcd_put_cur(LCD_I2C, 2, 0);
    lcd_send_string(LCD_I2C, lcdString);

    toggle_gpio(GPIOC, 8);

    DelayMS(750); // Max6675 delay is 250ms
  }
}
