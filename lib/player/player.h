#ifndef LIB_PLAYER_PLAYER_H_
#define LIB_PLAYER_PLAYER_H_

// own lib
#include "screen_info.h"
#include "asset.h"

// c lib
#include <cinttypes>


class Player {
 public:
  explicit Player(int16_t x_position, Asset asset);
  ~Player() {}
  void Jump();
  void UpdateYPosition();
  bool OnGround();
  int16_t GetYPosition() const;
  int16_t GetXPosition() const;
  template <typename TRenderer> void Draw(TRenderer *renderer) {
    m_asset.Draw(GetXPosition(), GetYPosition(), renderer);
  }
 private:
  int16_t m_y_position = 0;  // 0 is on the ground, negative is invalid
  int16_t m_x_position = 0;
  int16_t m_y_velocity = 0;  // positive is going up, negative is falling down

  // for the jumping algorithm
  static const uint8_t kGravity = 1;
  static const uint8_t kJumpVelocity = 9;

  // asset
  Asset m_asset;
};

#endif  // LIB_PLAYER_PLAYER_H_
