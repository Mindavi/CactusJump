enum gameState {
  start,
  hiscore,
  play,
  gameOver
};


gameState game_state = start;

inline void nextGameState() {
  game_state = static_cast<gameState>((game_state + 1) % (gameOver + 1));
}
