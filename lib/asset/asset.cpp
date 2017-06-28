#include "asset.h"
#include "screen_info.h"

Asset::Asset(uint16_t width, uint16_t height, unsigned char* bitmap)
  : m_width(width),
    m_height(height),
    m_bitmap(bitmap) {}

uint16_t Asset::GetHeight() const {
  return m_height;
}

uint16_t Asset::GetWidth() const {
  return m_width;
}

unsigned char* Asset::GetBitmap() const {
  return m_bitmap;
}

void Asset::Draw(
  uint16_t x,
  uint16_t y,
  U8G2_SSD1306_128X64_NONAME_F_HW_I2C* renderer) {
    int16_t y_position_from_ground = kScreenHeight - GetHeight() - y;
    renderer->drawXBM(
      x,
      y_position_from_ground,
      GetWidth(),
      GetHeight(),
      GetBitmap());
}
