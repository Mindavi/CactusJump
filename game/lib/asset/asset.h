#ifndef GAME_LIB_ASSET_ASSET_H_
#define GAME_LIB_ASSET_ASSET_H_

#include <cinttypes>

class Asset {
 public:
  Asset(uint16_t width, uint16_t height, unsigned char* bitmap);
  uint16_t getWidth();
  uint16_t getHeight();
  unsigned char* getBitmap();
 private:
  uint16_t m_width;
  uint16_t m_height;
  unsigned char* m_bitmap;
};

#endif  // GAME_LIB_ASSET_ASSET_H_
