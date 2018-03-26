#include "obstacle.h"
#include "screen_info.h"

Obstacle::Obstacle(Asset obstacle_asset)
  : m_asset(obstacle_asset),
    m_x_position(kScreenWidth + obstacle_asset.GetWidth())  // right of screen
{}

bool Obstacle::CollidesWith(const Player& player) const {
  if (player.GetXPosition()) {
    //
  }
  return false;
}

void Obstacle::UpdateXPosition() {
  m_x_position += m_x_velocity;
}

int16_t Obstacle::GetXPosition() const {
  return m_x_position;
}

