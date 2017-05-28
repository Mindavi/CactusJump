#include "game.h"

Game(Asset player_asset, Asset* object_assets, uint8_t object_assets_length)
  : m_player_asset(player_asset),
    m_object_assets(object_assets),
    m_object_assets_length(object_assets_length),
    m_state(start),
    m_distance_traveled(0) {}

void Game::NextGameState() {
  m_state = static_cast<GameState>((m_state + 1) % (kGameOver + 1));
}

void Game::Draw() {
  // update drawings
}

void Game::Update(bool button_pressed) {
  switch (m_state) {
    case kStart:
      Start(button_pressed);
      break;
    case kHiscore:
      Hiscore(button_pressed);
      break;
    case kPlay:
      Play(button_pressed);
      break;
    case kGameOver:
      GameOver(button_pressed);
      break;
    default:
      break;
  }
}

void Game::Start(bool button_pressed) {
  if (button_pressed) {
    NextGameState();
  }
}

void Game::Hiscore(bool button_pressed) {
  if (button_pressed) {
    NextGameState();
  }
}

void Game::Play(bool button_pressed) {
  if (button_pressed) {
    if (m_player.OnGround()) {
      m_player.jump();
    }
  }

  m_player.updateYPosition();
  UpdateObstaclePositions();

  if (CollisionDetected()) {
    NextGameState();
    break;
  }
  m_distance_traveled += 1;
}

void Game::GameOver(bool button_pressed) {
  // End of game?
}

void Game::UpdateObstaclePositions() {
  // update positions
}

bool Game::CollisionDetected() {
  // detect collisions
  return false;
}

uint32_t Game::GetScore() {
  return m_distance_traveled * kScorePerTick;
}
