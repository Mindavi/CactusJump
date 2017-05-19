#include <Arduino.h>
#include <stdio.h>

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

// for the jumping algorithm
const int gravity = 1;
const int jump_velocity = 8;

// global game state
gameState game_state = start;
int16_t player_y_position = 0; // 0 is on the ground, negative is invalid
int16_t player_y_velocity = 0; // positive is going up, negative is falling down
uint32_t distance_traveled = 0; // start at 0, represents score

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0);

Bounce button;

void setup(void) {
  u8g2.begin();
  u8g2.setFlipMode(0);
  u8g2.setFont(u8g2_font_artossans8_8r);
  pinMode(buttonPin, INPUT_PULLUP);
  button.attach(buttonPin);
  button.interval(10);
  Serial.begin(115200);
}

inline void nextGameState() {
  game_state = static_cast<gameState>((game_state + 1) % (gameOver + 1));
}

void drawPlayer(int y_position = 0)
{
  int y_position_from_beneath = screenHeight - player_height - y_position ;
  u8g2.drawXBM(((screenWidth / 3) - (player_width / 2)), y_position_from_beneath, player_width, player_height, player_bits);
}

void drawObstacles() {
  // TODO: draw obstacles according to the values in some array
}


void drawBootupScreen(void)
{
  int logoMiddleHorizontal = (screenWidth / 2) - (bootup_width / 2);
  int logoMiddleVertical = (screenHeight / 2) - (bootup_height / 2);
  u8g2.drawXBM(logoMiddleHorizontal, logoMiddleVertical, bootup_width, bootup_height, bootup_bits);
}

const int x_pos_gameover = 20;
const int y_pos_gameover = 20;
void drawGameOver(void) {
  u8g2.drawStr(x_pos_gameover, y_pos_gameover, "GAME OVER");
  // TODO: draw fancy asset?
}

const int x_pos_score = 20;
const int y_pos_score = 60;
const size_t score_buffer_size = 20;
void drawScore(void) {
  char scorebuffer[score_buffer_size];
  snprintf(scorebuffer, score_buffer_size, "Score: %u", distance_traveled);
  u8g2.drawStr(x_pos_score, y_pos_score, scorebuffer);
}

const int x_pos_hiscore = 0;
const int y_pos_hiscore = 20;
void drawHiscoreScreen(void) {
  u8g2.drawStr(x_pos_hiscore, y_pos_hiscore, "HI SCORES");
  // TODO: draw hi scores
}

bool collisionDetected(void) {
  /*
  if player_right_x_position >= obstacle_left_x_position and
    player_left_x_position <= obstacle_right_x_position
    player_bottom_y_position <= obstacle_top_y_position
  */

  // TODO: implement algorithm, remove auto logic
  return distance_traveled > random(100, 250);
}

inline bool playerOnGround(void) {
  return player_y_position == 0;
}

void updatePlayerYPosition(void) {
  // player stops falling when ground is hit
  if (playerOnGround() && player_y_velocity <= 0) {
    player_y_velocity = 0;
    return;
  }
  else if (!playerOnGround() || player_y_velocity > 0) {
    // increment height with velocity, also if velocity is negative (falling)
    player_y_position += player_y_velocity;
    if (player_y_position < 0) {
      player_y_position = 0;
    }
    // subtract gravity from velocity
    player_y_velocity -= gravity;
  }
}

void updateObstaclePosition(void) {
  // TODO
}

void updateScore(void) {
  distance_traveled += 1;
}

// unconditional jump ;-)
void jump(void) {
  player_y_velocity = jump_velocity;
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

  // clear buffer to start drawing
  u8g2.clearBuffer();

  switch (game_state)
  {
    case start:
      {
        drawBootupScreen();
        if (buttonPressed) {
          nextGameState();
        }
        break;
      }
    case hiscore:
      {
        drawHiscoreScreen();
        if (buttonPressed) {
          nextGameState();
        }
        break;
      }
    case play:
      {
        if (buttonPressed) {
          if (playerOnGround()) {
            jump();
          }
        }

        updatePlayerYPosition();
        updateObstaclePosition();
        drawPlayer(player_y_position);
        drawObstacles();

        if (collisionDetected()) {
          nextGameState();
          break;
        }
        // happens after collision detection, so score will only get higher
        // if player does not collide
        updateScore();
        break;
      }
    case gameOver:
      {
        drawGameOver();
        drawScore();
        if (buttonPressed) {
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
  // draw everything on the screen
  u8g2.sendBuffer();
}
