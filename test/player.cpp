#include "gtest/gtest.h"
#include "player.h"
#include "asset.h"

static const uint16_t width = 2;
static const uint16_t height = 3;
static unsigned char* bitmap = (unsigned char*)"test";
Asset player_asset(width, height, bitmap);

TEST(player_test, constructor_test) {
  int16_t x_position = 5;
  Player player(x_position, player_asset);
  ASSERT_EQ(x_position, player.GetXPosition());
  ASSERT_TRUE(player.OnGround());
  ASSERT_EQ(0, player.GetYPosition());
}

TEST(player_test, jump_test) {
  int16_t x_position = 5;
  int16_t y_position_on_ground = 0;
  Player player(x_position, player_asset);
  ASSERT_TRUE(player.OnGround());
  player.Jump();
  ASSERT_EQ(y_position_on_ground, player.GetYPosition());
  player.UpdateYPosition();
  ASSERT_NE(y_position_on_ground, player.GetYPosition());
}
