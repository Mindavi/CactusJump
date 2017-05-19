#include "Player.hpp"

Player::Player() {}

uint32_t Player::getScore() {
  return m_distance_traveled;
}

void Player::jump() {
  m_y_velocity = kJumpVelocity;
}

void Player::updateScore() {
  m_distance_traveled += kScorePerTick;
}

bool Player::onGround() {
  return m_y_position == 0;
}

void Player::updateYPosition() {
  // player stops falling when ground is hit
  if (onGround() && m_y_velocity <= 0) {
    m_y_velocity = 0;
    return;
  }
  else if (!onGround() || m_y_velocity > 0) {
    // increment height with velocity, also if velocity is negative (falling)
    m_y_position += m_y_velocity;
    if (m_y_position < 0) {
      m_y_position = 0;
    }
    // subtract gravity from velocity
    m_y_velocity -= kGravity;
  }
}
