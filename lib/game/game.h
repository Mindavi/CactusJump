#ifndef LIB_GAME_GAME_H_
#define LIB_GAME_GAME_H_

#include "player.h"
#include "asset.h"
#include "obstacle.h"
#include "game_state.h"
#include "screen_info.h"
#include <U8g2lib.h>

class Game {
 public:
  Game(Asset bootup_screen,
    Asset player_asset,
    Obstacle* obstacles,
    uint8_t obstacles_length,
    U8G2_SSD1306_128X64_NONAME_F_HW_I2C* renderer);
  ~Game() {}
  void Draw();
  void Update(bool button_pressed);
  uint32_t GetScore();

 private:
  Asset m_bootup_screen;
  Obstacle* m_obstacles;
  uint8_t m_obstacles_length;
  Player m_player;
  GameState m_state;
  uint32_t m_distance_traveled;  // represents score
  U8G2_SSD1306_128X64_NONAME_F_HW_I2C* m_renderer;
  static const uint8_t kScorePerTick = 1;
  void Start(bool button_pressed);
  void Hiscore(bool button_pressed);
  void Play(bool button_pressed);
  void GameOver(bool button_pressed);
  void NextGameState();
  void UpdateObstaclePositions();
  bool CollisionDetected();
  void DrawBootupScreen();
  void DrawHiscoreScreen();
  void DrawPlayer();
  void DrawObstacles();
  void DrawGameOver();
  void DrawScore();
};

#endif  // LIB_GAME_GAME_H_
