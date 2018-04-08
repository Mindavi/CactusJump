#include "obstacle.h"
#include "screen_info.h"

Obstacle::Obstacle(Asset obstacle_asset, int16_t x_position)
  : m_asset(obstacle_asset),
    m_x_position(x_position)
{}

Obstacle::Obstacle(Asset obstacle_asset)
  : m_asset(obstacle_asset),
    m_x_position(kScreenWidth + obstacle_asset.GetWidth())  // right of screen
{}

bool Obstacle::CollidesWith(const Player& player) const {
  int16_t left_player = player.GetXPosition() - (player.GetWidth() / 2.0f);
  int16_t right_player = player.GetXPosition() + (player.GetWidth() / 2.0f);

  int16_t left_obstacle = m_x_position - (m_asset.GetWidth() / 2.0f);
  int16_t right_obstacle = m_x_position + (m_asset.GetWidth() / 2.0f);
  
  if (right_player > left_obstacle && left_player < right_obstacle) {
    return true;
  }
  return false;
}

void Obstacle::UpdateXPosition() {
  m_x_position += m_x_velocity;
}

int16_t Obstacle::GetXPosition() const {
  return m_x_position;
}

