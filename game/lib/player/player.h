#ifndef GAME_LIB_PLAYER_PLAYER_H_
#define GAME_LIB_PLAYER_PLAYER_H_

#include <cinttypes>

class Player {
 public:
  Player();
  void updateScore();
  uint32_t getScore();
  void jump();
  void updateYPosition();
  bool onGround();
  int16_t getYPosition();
 private:
  uint32_t m_distance_traveled = 0;  // start at 0, represents score
  int16_t m_y_position = 0;  // 0 is on the ground, negative is invalid
  int16_t m_y_velocity = 0;  // positive is going up, negative is falling down

  // for the jumping algorithm
  static const uint8_t kGravity = 1;
  static const uint8_t kJumpVelocity = 8;
  static const uint8_t kScorePerTick = 1;
};

#endif  // GAME_LIB_PLAYER_PLAYER_H_
