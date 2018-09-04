#include "game.h"

Game::Game(Asset bootup_screen,
  Asset player_asset,
  Obstacle* obstacles,
  uint8_t obstacles_length,
  U8G2_SSD1306_128X64_NONAME_F_HW_I2C* renderer)
  : m_bootup_screen(bootup_screen),
    m_obstacles(obstacles),
    m_obstacles_length(obstacles_length),
    m_current_obstacle(nullptr),
    m_player((kScreenWidth / 3) - (player_asset.GetWidth() / 2), player_asset),
    m_state(GameState::kStart),
    m_distance_traveled(0),
    m_renderer(renderer) {}

void Game::NextGameState() {
  switch (m_state) {
    case GameState::kStart:
      {
        m_state = GameState::kHiscore;
        break;
      }
    case GameState::kHiscore:
      {
        m_state = GameState::kPlay;
        break;
      }
    case GameState::kPlay:
      {
        m_state = GameState::kStart;
        break;
      }
    default:
      {
        m_state = GameState::kStart;
        break;
      }
  }
}

void Game::Draw() {
  // clear buffer to start drawing
  m_renderer->clearBuffer();

  // update graphics
  switch (m_state) {
    case GameState::kStart:
      {
        DrawBootupScreen();
        break;
      }
    case GameState::kHiscore:
      {
        DrawHiscoreScreen();
        break;
      }
    case GameState::kPlay:
      {
        DrawPlayer();
        DrawObstacle();
        break;
      }
    case GameState::kGameOver:
      {
        DrawScore();
        break;
      }
    default:
      {
        Serial.println("invalid game state");
        // Restart the game if game state becomes invalid
        m_state = GameState::kStart;
        break;
      }
  }

  // draw everything on the screen
  m_renderer->sendBuffer();
}

void Game::Update(bool button_pressed) {
  switch (m_state) {
    case GameState::kStart:
      Start(button_pressed);
      break;
    case GameState::kHiscore:
      Hiscore(button_pressed);
      break;
    case GameState::kPlay:
      Play(button_pressed);
      break;
    case GameState::kGameOver:
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
    m_player.Jump();
  }

  UpdateObstacle();

  m_player.UpdateYPosition();

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

void Game::DrawObstacle() {
  if (m_current_obstacle != nullptr) {
      m_current_obstacle->Draw(m_renderer);
  }
}

void Game::UpdateObstacle() {
  if (m_obstacles_length <= 0) {
    return;
  }
  if (m_current_obstacle == nullptr) {
    // TODO: choose random obstacle
    m_current_obstacle = &m_obstacles[0];
  }
  auto off_screen = 0 - m_current_obstacle->GetWidth();
  if (m_current_obstacle->GetXPosition() <= off_screen) {
    m_current_obstacle->Reset();
    m_current_obstacle = nullptr;
    return;
  }
  m_current_obstacle->UpdateXPosition();
}

bool Game::CollisionDetected() {
  return m_current_obstacle->CollidesWith(m_player);
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

void Game::DrawScore() {
  static const uint8_t kScoreX = 20;
  static const uint8_t kScoreY = 60;
  static const size_t kScoreBufferSize = 20;
  char score_buffer[kScoreBufferSize];
  snprintf(score_buffer, kScoreBufferSize, "Score: %u", GetScore());
  m_renderer->drawStr(kScoreX, kScoreY, score_buffer);
}
