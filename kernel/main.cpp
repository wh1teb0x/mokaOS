#include <cstdio>
#include <stdint.h>
#include <stddef.h>
#include <cstdarg>

#include "frame_buffer_config.hpp"
#include "graphics.hpp"
#include "font.hpp"
#include "console.hpp"
#include "pci.hpp"
#include "mouse.hpp"
#include "logger.hpp"

void operator delete(void* obj) noexcept {}

extern "C" void __cxa_pure_virtual() {
  while (1) __asm__("hlt");
}

const PixelColor kDesktopBGColor{45, 118, 237};
const PixelColor kDesktopFGColor{255, 255, 255};

char pixel_writer_buf[sizeof(RGBResv8BitPerColorPixelWriter)];
PixelWriter* pixel_writer;

char console_buf[sizeof(Console)];
Console* console;

int printk(const char* format, ...) {
  va_list ap;
  int result;
  char s[1024];

  va_start(ap, format);
  result = vsprintf(s, format, ap);
  va_end(ap);

  console->PutString(s);
  return result;
}

extern "C" void KernelMain(const FrameBufferConfig& frame_buffer_config) {
  switch (frame_buffer_config.pixel_format) {
    case kPixelBGRResv8BitPerColor:
      pixel_writer = new (pixel_writer_buf)
          BGRResv8BitPerColorPixelWriter(frame_buffer_config);
      break;
    case kPixelRGBResv8BitPerColor:
      pixel_writer = new (pixel_writer_buf)
          RGBResv8BitPerColorPixelWriter(frame_buffer_config);
      break;
  }

  const int kFrameWidth = frame_buffer_config.horizontal_resolution;
  const int kFrameHeight = frame_buffer_config.vertical_resolution;

  FillRectangle(*pixel_writer, {0, 0}, {kFrameWidth, kFrameHeight - 50},
                kDesktopBGColor);
  FillRectangle(*pixel_writer, {0, kFrameHeight - 50}, {kFrameWidth, 50},
                {1, 8, 17});
  FillRectangle(*pixel_writer, {0, kFrameHeight - 50}, {kFrameWidth / 5, 50},
                {80, 80, 80});
  DrawRectangle(*pixel_writer, {10, kFrameHeight - 40}, {30, 30},
                {160, 160, 160});

  console = new (console_buf)
      Console{*pixel_writer, kDesktopFGColor, kDesktopBGColor};
  printk("Welcome to MokaOS!\n");

  SetLogLevel(kWarn);

  while (1) __asm__("hlt");
}