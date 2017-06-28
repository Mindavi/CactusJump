#ifndef LIB_OBSTACLE_OBSTACLE_H__
#define LIB_OBSTACLE_OBSTACLE_H__

#include "screen_info.h"
#include <cinttypes>

class Obstacle {
 public:
  explicit Obstacle(Asset obstacle_asset);
  ~Obstacle() {}
  void UpdateYPosition();
  int16_t GetYPosition() const;
  bool CollidesWith(const Player& player) const;
 private:
  int16_t m_y_position = 0;
}

#endif  // LIB_OBSTACLE_OBSTACLE_H__
