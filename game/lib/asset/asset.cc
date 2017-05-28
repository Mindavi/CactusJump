#include "asset.h"

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

void Asset::Draw(uint16_t x,
  uint16_t y,
  U8G2_SSD1306_128X64_NONAME_F_HW_I2C* renderer) {
    renderer->drawXBM(
      x,
      y,
      getWidth(),
      getHeight(),
      getBitmap());
}
