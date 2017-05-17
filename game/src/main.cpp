#include <Arduino.h>

#include <Bounce2.h>
#include <U8g2lib.h>

#include "logo.h"
#include "player_dick.h"
#include "gameState.h"

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

const int buttonPin = D3;
const int screenWidth = 128;
const int screenHeight = 64;

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0);

Bounce button;

void setup(void) {
  u8g2.begin();
  u8g2.setFlipMode(0);
  pinMode(buttonPin, INPUT_PULLUP);
  button.attach(buttonPin);
  button.interval(10);
  Serial.begin(115200);
}

void drawPlayer(int y_position = 0)
{
  int y_position_from_beneath = screenHeight - player_height - y_position ;
  u8g2.drawXBM(((screenWidth / 3) - (player_width / 2)), y_position_from_beneath, player_width, player_height, player_bits);
}

void drawBootupscreen(void)
{
  int logoMiddleHorizontal = (screenWidth / 2) - (bootup_width / 2);
  int logoMiddleVertical = (screenHeight / 2) - (bootup_height / 2);
  u8g2.drawXBM(logoMiddleHorizontal, logoMiddleVertical, bootup_width, bootup_height, bootup_bits);
}


void loop(void) {
  // in the loop so it's only true once, after this it's false again.
  //This is so it won't think the button is pressed again every loop.
  bool buttonPressed = false;

  if (button.update())
  {
    buttonPressed = button.read();
    Serial.println("Button update");
  }

  u8g2.clearBuffer();

  switch (game_state)
  {
    case start:
      {
        drawBootupscreen();
        if (buttonPressed) {
          nextGameState();
        }
        break;
      }
    case hiscore:
      {
        if (buttonPressed) {
          nextGameState();
        }
        break;
      }
    case play:
      {
        int player_position = 0;
        if (buttonPressed) {
          static int timesPressed = 0;
          timesPressed = timesPressed + 1;
          if (timesPressed == 10) {
            timesPressed = 0;
            nextGameState();
          }
          player_position = 10;
        }
        drawPlayer(player_position);

        break;
      }
    case gameOver:
      {
        if (buttonPressed) {
          nextGameState();
        }
        break;
      }
  }

  u8g2.sendBuffer();
}
