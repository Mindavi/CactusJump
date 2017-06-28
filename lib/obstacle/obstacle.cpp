#include "obstacle.h"
#include "screen_info.h"

Obstacle::Obstacle(Asset obstacle_asset)
  : m_asset(obstacle_asset),
    m_y_position(kScreenWidth + obstacle_asset.GetWidth())  // right of screen
{}

Obstacle::CollidesWith(const Player& player) {
  if (player.GetXPosition()) {
    //
  }
}
