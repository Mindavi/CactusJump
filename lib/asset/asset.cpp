#include "asset.h"

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
