#ifndef LIB_ASSET_ASSET_H_
#define LIB_ASSET_ASSET_H_

#include "screen_info.h"

#include <cinttypes>

class Asset {
 public:
  Asset(uint16_t width, uint16_t height, unsigned char* bitmap);
  uint16_t GetWidth() const;
  uint16_t GetHeight() const;
  unsigned char* GetBitmap() const;
  template <typename TRenderer> void Draw(
    uint16_t x,
    uint16_t y,
    TRenderer* renderer) {
      int16_t y_position_from_ground = kScreenHeight - GetHeight() - y;
      renderer->drawXBM(
        x,
        y_position_from_ground,
        GetWidth(),
        GetHeight(),
        GetBitmap());
  }
 private:
  uint16_t m_width;
  uint16_t m_height;
  unsigned char* m_bitmap;
};

#endif  // LIB_ASSET_ASSET_H_
