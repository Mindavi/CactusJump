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
gameState game_state = start;

// The player in the game
Player player;

// Assets
Asset player_asset(player_width, player_height, player_bits);
Asset logo_asset(bootup_width, bootup_height, bootup_bits);

// The display object
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0);

Bounce button;

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


inline void nextGameState() {
  game_state = static_cast<gameState>((game_state + 1) % (gameOver + 1));
}

void drawPlayer(uint16_t y = 0) {
  int16_t y_position_from_ground = kScreenHeight - player_asset.getHeight() - y;
  int16_t player_x = ((kScreenWidth / 3) - (player_asset.getHeight() / 2));
  u8g2.drawXBM(
    player_x,
    y_position_from_ground,
    player_asset.getHeight(),
    player_asset.getHeight(),
    player_asset.getBitmap());
}

void drawObstacles() {
  // TODO: draw obstacles according to the values in some array
}


void drawBootupScreen() {
  int16_t logoMiddleX = (kScreenWidth / 2) - (bootup_width / 2);
  int16_t logoMiddleY = (kScreenHeight / 2) - (bootup_height / 2);
  u8g2.drawXBM(
    logoMiddleX,
    logoMiddleY,
    bootup_width,
    bootup_height,
    bootup_bits);
}

void drawGameOver() {
  static const uint8_t x_pos_gameover = 20;
  static const uint8_t y_pos_gameover = 20;
  u8g2.drawStr(x_pos_gameover, y_pos_gameover, "GAME OVER");
  // TODO: draw fancy asset?
}


void drawScore() {
  static const uint8_t kScoreX = 20;
  static const uint8_t kScoreY = 60;
  static const size_t kScoreBufferSize = 20;
  char score_buffer[kScoreBufferSize];
  snprintf(score_buffer, kScoreBufferSize, "Score: %u", player.getScore());
  u8g2.drawStr(kScoreX, kScoreY, score_buffer);
}

void drawHiscoreScreen() {
  static const uint8_t kHiscoreX = 0;
  static const uint8_t kHiscoreY = 20;
  u8g2.drawStr(kHiscoreX, kHiscoreY, "HI SCORES");
  // TODO: draw hi scores
}

bool collisionDetected() {
  /*
  if player_right_x_position >= obstacle_left_x_position and
    player_left_x_position <= obstacle_right_x_position
    player_bottom_y_position <= obstacle_top_y_position
  */

  // TODO: implement algorithm, remove auto logic
  return player.getScore() > (unsigned)random(100, 250);
}

void updateObstaclePosition() {
  // TODO
}

void resetGame() {
  player = Player();
}

void updateGameLogic(bool button_pressed) {
  switch (game_state) {
    case start:
      {
        if (button_pressed) {
          nextGameState();
        }
        break;
      }
    case hiscore:
      {
        if (button_pressed) {
          nextGameState();
        }
        break;
      }
    case play:
      {
        if (button_pressed) {
          if (player.onGround()) {
            player.jump();
          }
        }

        player.updateYPosition();
        updateObstaclePosition();

        if (collisionDetected()) {
          nextGameState();
          break;
        }
        // happens after collision detection, so score will only get higher
        // if player does not collide
        player.updateScore();
        break;
      }
    case gameOver:
      {
        if (button_pressed) {
          resetGame();
          nextGameState();
        }
        break;
      }
    default:
      {
        Serial.println("Invalid game state");
        break;
      }
  }
}

void updateGameGraphics() {
  // clear buffer to start drawing
  u8g2.clearBuffer();

  // update graphics
  switch (game_state) {
    case start:
      {
        drawBootupScreen();
        break;
      }
    case hiscore:
      {
        drawHiscoreScreen();
        break;
      }
    case play:
      {
        drawPlayer(player.getYPosition());
        drawObstacles();
        break;
      }
    case gameOver:
      {
        drawGameOver();
        drawScore();
        break;
      }
    default:
      {
        Serial.println("invalid game state");
        break;
      }
  }

  // draw everything on the screen
  u8g2.sendBuffer();
}

void loop(void) {
  // In the loop so it's only true once, after this it's false again.
  // This is so it won't think the button is pressed again every loop.
  bool buttonPressed = false;

  if (button.update()) {
    buttonPressed = button.read();
    Serial.println("Button update");
  }

  updateGameLogic(buttonPressed);
  updateGameGraphics();
}
