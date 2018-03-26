#include "game.h"

Game::Game(Asset bootup_screen,
  Asset player_asset,
  Asset* object_assets,
  uint8_t object_assets_length,
  U8G2_SSD1306_128X64_NONAME_F_HW_I2C* renderer)
  : m_bootup_screen(bootup_screen),
    m_object_assets(object_assets),
    m_object_assets_length(object_assets_length),
    m_player((kScreenWidth / 3) - (player_asset.GetWidth() / 2), player_asset),
    m_state(kStart),
    m_distance_traveled(0),
    m_renderer(renderer) {}

void Game::NextGameState() {
  m_state = static_cast<GameState>((m_state + 1) % (kGameOver + 1));
}

void Game::Draw() {
  // clear buffer to start drawing
  m_renderer->clearBuffer();

  // update graphics
  switch (m_state) {
    case kStart:
      {
        DrawBootupScreen();
        break;
      }
    case kHiscore:
      {
        DrawHiscoreScreen();
        break;
      }
    case kPlay:
      {
        DrawPlayer();
        DrawObstacles();
        break;
      }
    case kGameOver:
      {
        DrawGameOver();
        DrawScore();
        break;
      }
    default:
      {
        Serial.println("invalid game state");
	// Restart the game if game state becomes invalid
	m_state = kStart;
        break;
      }
  }

  // draw everything on the screen
  m_renderer->sendBuffer();
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
    m_distance_traveled = 0;
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
      m_player.Jump();
    }
  }

  m_player.UpdateYPosition();
  UpdateObstaclePositions();

  if (CollisionDetected()) {
    NextGameState();
    return;
  }
  m_distance_traveled += 1;
}

void Game::GameOver(bool button_pressed) {
  if (button_pressed) {
    NextGameState();
  }
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

void Game::DrawBootupScreen() {
  int16_t logoMiddleX = (kScreenWidth / 2) - (m_bootup_screen.GetWidth() / 2);
  int16_t logoMiddleY = (kScreenHeight / 2) - (m_bootup_screen.GetHeight()/ 2);
  m_bootup_screen.Draw(logoMiddleX, logoMiddleY, m_renderer);
}

void Game::DrawHiscoreScreen() {
  static const uint8_t kHiscoreX = 0;
  static const uint8_t kHiscoreY = 20;
  m_renderer->drawStr(kHiscoreX, kHiscoreY, "HI SCORES");
  // TODO: draw hi scores
}

void Game::DrawPlayer() {
  m_player.Draw(m_renderer);
}

void Game::DrawObstacles() {
  for (size_t i = 0; i < m_object_assets_length; i++) {
    int16_t y_position = 0;
    int16_t x_position = ((kScreenWidth / 3) * 2 -
                          (m_object_assets[i].GetWidth() / 2));
    m_object_assets[i].Draw(x_position, y_position, m_renderer);
  }
}

void Game::DrawGameOver() {
  // maybe unneeded, DrawScore() is called when game over
}

void Game::DrawScore() {
  static const uint8_t kScoreX = 20;
  static const uint8_t kScoreY = 60;
  static const size_t kScoreBufferSize = 20;
  char score_buffer[kScoreBufferSize];
  snprintf(score_buffer, kScoreBufferSize, "Score: %u", GetScore());
  m_renderer->drawStr(kScoreX, kScoreY, score_buffer);
}
