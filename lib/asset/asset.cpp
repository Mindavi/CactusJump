#include "asset.h"
#include "screen_info.h"

Asset::Asset(uint16_t width, uint16_t height, unsigned char* bitmap)
  : m_width(width),
    m_height(height),
    m_bitmap(bitmap) {}

uint16_t Asset::getHeight() {
  return m_height;
}

uint16_t Asset::getWidth() {
  return m_width;
}

unsigned char* Asset::getBitmap() {
  return m_bitmap;
}

void Asset::Draw(
  uint16_t x,
  uint16_t y,
  U8G2_SSD1306_128X64_NONAME_F_HW_I2C* renderer) {
    int16_t y_position_from_ground = kScreenHeight - getHeight() - y;
    renderer->drawXBM(
      x,
      y_position_from_ground,
      getWidth(),
      getHeight(),
      getBitmap());
}
