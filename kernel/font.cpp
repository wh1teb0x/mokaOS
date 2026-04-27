#include "font.hpp"

extern const uint8_t _binary_hankaku_bin_start;
extern const uint8_t _binary_hankaku_bin_end;
extern const uint8_t _binary_hankaku_bin_size;

const uint8_t* GetFont(char c) {
  auto index = 16 * static_cast<unsigned int>(c);
  if (index >= reinterpret_cast<uintptr_t>(&_binary_hankaku_bin_size)) {
    return nullptr;
  }
  return &_binary_hankaku_bin_start + index;
}

void WriteAscii(PixelWriter& writer, int x, int y, char c, const PixelColor& color){ 
  const uint8_t* font = GetFont(c);
  if (font == nullptr) {
    return;
  }
  for (int dy = 0; dy < 16; ++dy) {
    for (int dx = 0; dx < 8; ++dx) {
      if ((font[dy] << dx) & 0x80u) { // left shift the bits of the font data. 0x80 is 10000000 in binary
        writer.Write(x + dx, y + dy, color);
      }
    }
  }
}

void WriteString(PixelWriter& writer, int x, int y, const char* s, const PixelColor& color) {
  // Loop through each character in the string until we reach the null terminator.
  for (int i = 0; s[i] != '\0'; ++i) {
    // each character is 8 pixels wide, so we calculate the x position for each character by adding 8 * i to the initial x position. 
    WriteAscii(writer, x + 8 * i, y, s[i], color);
  }
}