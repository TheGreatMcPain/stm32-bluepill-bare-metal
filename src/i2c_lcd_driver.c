/*
 * Based on controllerstech's LCD2004 I2C driver.
 */
#include "i2c_lcd_driver.h"

#define SLAVE_ADDRESS_LCD 0x4E

void lcd_send_cmd(uint8_t i2c, char cmd) {
  char data_u, data_l;
  uint8_t data_t[4];
  data_u = (cmd & 0xf0);
  data_l = ((cmd << 4) & 0xf0);

  data_t[0] = data_u | 0x0C; // en=1, rs=0
  data_t[1] = data_u | 0x08; // en=0, rs=0
  data_t[2] = data_l | 0x0C; // en=1, rs=0
  data_t[3] = data_l | 0x08; // en=0, rs=0

  i2c_write(i2c, SLAVE_ADDRESS_LCD, 0, (uint8_t *)data_t, 4);
}

void lcd_send_data(uint8_t i2c, char data) {
  char data_u, data_l;
  uint8_t data_t[4];
  data_u = (data & 0xf0);
  data_l = ((data << 4) & 0xf0);

  data_t[0] = data_u | 0x0D; // en=1, rs=1
  data_t[1] = data_u | 0x09; // en=0, rs=1
  data_t[2] = data_l | 0x0D; // en=1, rs=1
  data_t[3] = data_l | 0x09; // en=0, rs=1

  i2c_write(i2c, SLAVE_ADDRESS_LCD, 0, (uint8_t *)data_t, 4);
}

void lcd_clear(uint8_t i2c) {
  lcd_send_cmd(i2c, 0x00);
  for (int i = 0; i < 100; i++) {
    lcd_send_data(i2c, ' ');
  }
}

void lcd_put_cur(uint8_t i2c, int row, int col) {
  switch (row) {
  case 0:
    col += 0x80 | 0x00;
    break;
  case 1:
    col += 0x80 | 0x40;
    break;
  case 2:
    col += 0x80 | 0x14;
    break;
  case 3:
    col += 0x80 | 0x54;
  }

  lcd_send_cmd(i2c, (char)col);
}

void lcd_init(uint8_t i2c) {
  // 4 bit initialization
  DelayMS(50); // wait for >40ms
  lcd_send_cmd(i2c, 0x30);
  DelayMS(5); // wait for >4.1ms
  lcd_send_cmd(i2c, 0x30);
  DelayMS(1); // wait for >100us
  lcd_send_cmd(i2c, 0x30);
  DelayMS(10);
  lcd_send_cmd(i2c, 0x20); // 4bit mode
  DelayMS(10);

  // display initialization
  lcd_send_cmd(i2c, 0x28); // Function set --> DL=0 (4 bit mode), N=1 (2 line
                           // display) F=0 (5x8 characters)
  DelayMS(1);

  lcd_send_cmd(i2c, 0x01); // clear display
  DelayMS(1);
  DelayMS(1);

  lcd_send_cmd(i2c, 0x06); // Entry mode set --> I/O=1 (increment cursor) & S=0
                           // (no shift)
  DelayMS(1);
  lcd_send_cmd(i2c, 0x0C); // Display on/off control --> D=1, C and B=0.
                           // (Cursor and blink, last two bits)
}

void lcd_send_string(uint8_t i2c, char *str) {
  while (*str)
    lcd_send_data(i2c, *str++);
}
