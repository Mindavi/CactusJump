#include "player.h"

Player::Player(int16_t x_position, Asset asset)
  : m_x_position(x_position),
    m_asset(asset)
{}

void Player::Jump() {
  m_y_velocity = kJumpVelocity;
}

bool Player::OnGround() {
  return m_y_position == 0;
}

void Player::UpdateYPosition() {
  // player stops falling when ground is hit
  if (OnGround() && m_y_velocity <= 0) {
    m_y_velocity = 0;
    return;
  } else if (!OnGround() || m_y_velocity > 0) {
    // increment height with velocity, also if velocity is negative (falling)
    m_y_position += m_y_velocity;
    if (m_y_position < 0) {
      m_y_position = 0;
    }
    // subtract gravity from velocity
    m_y_velocity -= kGravity;
  }
}

void Player::Draw(U8G2_SSD1306_128X64_NONAME_F_HW_I2C *renderer) {
  m_asset.Draw(GetXPosition(), GetYPosition(), renderer);
}

int16_t Player::GetYPosition() const {
  return m_y_position;
}

int16_t Player::GetXPosition() const {
  return m_x_position;
}
