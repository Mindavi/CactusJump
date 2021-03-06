#ifndef LIB_OBSTACLE_OBSTACLE_H__
#define LIB_OBSTACLE_OBSTACLE_H__

#include "asset.h"
#include "player.h"
#include "screen_info.h"
#include <cinttypes>

class Obstacle {
 public:
  explicit Obstacle(Asset obstacle_asset);
  Obstacle(Asset obstacle_asset, float x_position);
  ~Obstacle() {}
  void UpdateXPosition();
  int16_t GetXPosition() const;
  template <typename TRenderer> void Draw(TRenderer *renderer) {
    m_asset.Draw(GetXPosition(), 0, renderer);
  }
  bool CollidesWith(const Player& player) const;
  uint16_t GetWidth() const;
  void Reset();
  void SetVelocity(float velocity);
 private:
  Asset m_asset;
  float m_x_position = 0.0;
  float m_x_velocity = 2.0;
};

#endif  // LIB_OBSTACLE_OBSTACLE_H__
