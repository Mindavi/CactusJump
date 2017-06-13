// Copyright 2017 Rick van Schijndel

#include <Arduino.h>
#include <stdio.h>

#include <Bounce2.h>
#include <U8g2lib.h>

#include "logo.h"
#include "player_dick.h"
#include "game_state.h"
#include "asset.h"
#include "player.h"
#include "object.h"
#include "game.h"

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

const uint8_t kButtonPin = D3;
const uint8_t kScreenWidth = 128;
const uint8_t kScreenHeight = 64;

// Global game state
GameState game_state = kStart;

// The player in the game
Player player;

// Assets
Asset bootup_screen(bootup_width, bootup_height, bootup_bits);
Asset player_asset(player_width, player_height, player_bits);
Asset logo_asset(bootup_width, bootup_height, bootup_bits);
Asset object(object_width, object_height, object_bits);

// The display object
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0);

Bounce button;

Game game(bootup_screen, player_asset, &object, 1, &u8g2);

void setupButton() {
  pinMode(kButtonPin, INPUT_PULLUP);
  button.attach(kButtonPin);
  button.interval(10);
}

void setupGraphics() {
  u8g2.begin();
  u8g2.setFlipMode(0);
  u8g2.setFont(u8g2_font_artossans8_8r);
}

void setup(void) {
  setupGraphics();
  setupButton();
  Serial.begin(115200);
}

void loop(void) {
  // In the loop so it's only true once, after this it's false again.
  // This is so it won't think the button is pressed again every loop.
  bool buttonPressed = false;

  if (button.update()) {
    buttonPressed = button.read();
    Serial.println("Button update");
  }
  game.Update(buttonPressed);
  game.Draw();
}
