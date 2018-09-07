// Copyright 2017 Rick van Schijndel

#include <Arduino.h>

#include <Bounce2.h>
#include <U8g2lib.h>

// assets
#include "logo.xbm"
#include "player.xbm"
// obstacles
#include "coffee.xbm"
#include "bottle.xbm"
#include "mushroom.xbm"
#include "eye.xbm"

#include "asset.h"
#include "player.h"
#include "game.h"
#include "scorekeeper.h"
#include "FS.h"
#include "screen_info.h"

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

const uint8_t kButtonPin = D3;

// Assets
Asset bootup_screen(logo_width, logo_height, logo_bits);
Asset player_asset(player_width, player_height, player_bits);
// obstacles
Asset coffee_asset(coffee_width, coffee_height, coffee_bits);
Asset bottle_asset(bottle_width, bottle_height, bottle_bits);
Asset mushroom_asset(mushroom_width, mushroom_height, mushroom_bits);
Asset eye_asset(eye_width, eye_height, eye_bits);

// The display object
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0);

Bounce button;

Obstacle obstacles[] = {
  Obstacle(coffee_asset),
  Obstacle(bottle_asset),
  Obstacle(mushroom_asset),
  Obstacle(eye_asset),
};
const size_t obstacles_size = sizeof(obstacles) / sizeof(obstacles[0]);
ScoreKeeperDefault scorekeeper;

Game game(bootup_screen, player_asset, obstacles, obstacles_size, &scorekeeper, &u8g2);

void setupButton(void) {
  pinMode(kButtonPin, INPUT_PULLUP);
  button.attach(kButtonPin);
  button.interval(10);
}

void setupGraphics(void) {
  u8g2.begin();
  u8g2.setFlipMode(0);
  u8g2.setFont(u8g2_font_artossans8_8r);
}

void setup(void) {
  setupGraphics();
  setupButton();
  Serial.begin(115200);
  randomSeed(analogRead(0));
  SPIFFS.begin();
  // SPIFFS.format();  // make sure the spiffs gets formatted the first time
  delay(1000);
}

bool buttonPressed = false;

void loop(void) {
  button.update();
  buttonPressed = button.fell();
  game.Update(buttonPressed);
  game.Draw();
}
