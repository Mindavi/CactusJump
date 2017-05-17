#include <Arduino.h>
#include <U8g2lib.h>

#include "logo.h"
#include "player_dick.h"

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0);

void setup(void) {
  u8g2.begin();
  u8g2.setFlipMode(0);
  randomSeed(analogRead(A0));
}

void drawPlayer(void)
{
  u8g2.drawXBM(random(128 - player_width), random(64 - player_height), player_width, player_height, player_bits);
}

int position = 0;

void drawLogo(void)
{
  u8g2.drawXBM(position - bootup_width, 0, bootup_width, bootup_height, bootup_bits);
}

void loop(void) {
  u8g2.clearBuffer();
  drawPlayer();
  drawLogo();
  u8g2.sendBuffer();
  position = ++position % (128 + bootup_width); // for drawing from totally left to totally right
}

