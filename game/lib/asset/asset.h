#ifndef GAME_LIB_ASSET_ASSET_H_
#define GAME_LIB_ASSET_ASSET_H_

#include <cinttypes>
#include <U8g2lib.h>

class Asset {
 public:
  Asset(uint16_t width, uint16_t height, unsigned char* bitmap);
  uint16_t getWidth();
  uint16_t getHeight();
  unsigned char* getBitmap();
  void Draw(uint16_t x,
    uint16_t y,
    U8G2_SSD1306_128X64_NONAME_F_HW_I2C* renderer);
 private:
  uint16_t m_width;
  uint16_t m_height;
  unsigned char* m_bitmap;
};

#endif  // GAME_LIB_ASSET_ASSET_H_
