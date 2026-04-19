#include <stdint.h>

#include "frame_buffer_config.hpp"

struct PixelColor {
    uint8_t r;
    uint8_t g;
    uint8_t b;
};

int WritePixel(const FrameBufferConfig& config, int x, int y, const PixelColor& c) {
 const int pixel_position = config.pixels_per_scan_line * y + x;
 if (config.pixel_format == kPixelRGBResv8BitPerColor) {
   uint32_t color = (c.r << 16) | (c.g << 8) | c.b;
   *reinterpret_cast<uint32_t*>(config.frame_buffer + pixel_position * 4) = color;
 } else if (config.pixel_format == kPixelBGRResv8BitPerColor) {
   uint32_t color = (c.b << 16) | (c.g << 8) | c.r;
   *reinterpret_cast<uint32_t*>(config.frame_buffer + pixel_position * 4) = color;
 } else {
   return -1; // Unsupported pixel format.
 }
  return 0; // Success.
}

extern "C" void KernelMain(const FrameBufferConfig& frame_buffer_config){
  // Draw a simple gradient on the screen using the provided frame buffer configuration.
  for (uint32_t x = 0; x < frame_buffer_config.horizontal_resolution; ++x) {
    for (uint32_t y = 0; y < frame_buffer_config.vertical_resolution; ++y) {
      WritePixel(frame_buffer_config, x, y, {255, 255, 255});
    };
  };
  for (int x = 0; x < 200; ++x) {
    for (int y = 0; y < 100; ++y) {
      WritePixel(frame_buffer_config, 100 + x, 100 + y, {0, 255, 0});
    }
  }
  while (1) __asm__("hlt");
}