#ifndef LIB_OBSTACLE_OBSTACLE_H__
#define LIB_OBSTACLE_OBSTACLE_H__

#include "asset.h"
#include "player.h"
#include "screen_info.h"
#include <cinttypes>

class Obstacle {
 public:
  explicit Obstacle(Asset obstacle_asset);
  Obstacle(Asset obstacle_asset, int16_t x_position);
  ~Obstacle() {}
  void Draw();
  void UpdateXPosition();
  int16_t GetXPosition() const;
  template <typename TRenderer> void Draw(TRenderer *renderer) {
    m_asset.Draw(GetXPosition(), 0, renderer);
  }
  bool CollidesWith(const Player& player) const;
 private:
  Asset m_asset;
  int16_t m_x_position = 0;
  int16_t m_x_velocity = -1;  // backwards on x-axis, so towards player
};

#endif  // LIB_OBSTACLE_OBSTACLE_H__
