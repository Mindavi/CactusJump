#include "gtest/gtest.h"
#include "asset.h"
#include <string>

TEST(constructor_test, player_test) {
  uint16_t width = 2;
  uint16_t height = 4;
  unsigned char* bitmap = (unsigned char*)"abcdefgh";
  Asset asset(width, height, bitmap);
  ASSERT_EQ(asset.GetWidth(), width);
  ASSERT_EQ(asset.GetHeight(), height);
  ASSERT_TRUE(strcmp((const char*)asset.GetBitmap(), (const char*)bitmap) == 0);
}