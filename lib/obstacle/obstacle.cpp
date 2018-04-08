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
  int16_t left_player_x = player.GetXPosition();
  int16_t right_player_x = player.GetXPosition() + player.GetWidth();
  int16_t bottom_player = player.GetYPosition();

  int16_t left_obstacle_x = m_x_position;
  int16_t right_obstacle_x = m_x_position + m_asset.GetWidth();

  // assume object y == 0
  int16_t top_obstacle = m_asset.GetHeight();

  bool player_before_obstacle = right_player_x < left_obstacle_x;
  bool player_after_obstacle = left_player_x > right_obstacle_x;
  bool player_above_obstacle = bottom_player > top_obstacle;

  bool player_collides_x_obstacle = !player_before_obstacle && !player_after_obstacle;

  if (player_collides_x_obstacle && !player_above_obstacle) {
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

