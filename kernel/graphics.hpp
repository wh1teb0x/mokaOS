#pragma once

#include "frame_buffer_config.hpp"

struct PixelColor {
    uint8_t r;
    uint8_t g;
    uint8_t b;
};

class PixelWriter {
  public:
    PixelWriter(const FrameBufferConfig& config) : config_{config} { //constructor of PixelWriter
    }
    virtual ~PixelWriter() = default; // Virtual destructor to ensure proper cleanup of derived classes.
    virtual void Write(int x, int y, const PixelColor& c) = 0; // 0 means pure virtual function, which must be implemented by derived classes, which means interface of PixelWriter is defined by this function.

  protected:
    uint8_t* PixelAt(int x, int y) {
    return config_.frame_buffer + 4 * (config_.pixels_per_scan_line * y + x);
    }
  
  private:
    const FrameBufferConfig& config_;
};

class RGBResv8BitPerColorPixelWriter : public PixelWriter {
  public:
    using PixelWriter::PixelWriter; // Inherit the constructor of the base class PixelWriter. C++11 feature that allows the derived class to use the constructor of the base class without having to redefine it.
    virtual void Write(int x, int y, const PixelColor& c) override;
};

class BGRResv8BitPerColorPixelWriter : public PixelWriter {
  public:
    using PixelWriter::PixelWriter;

    virtual void Write(int x, int y, const PixelColor& c) override;
};

template <typename T>
struct Vector2D {
    T x, y;
};

void DrawRectangle(PixelWriter& writer, const Vector2D<int>& pos, const Vector2D<int>& size, const PixelColor& c);

void FillRectangle(PixelWriter& writer, const Vector2D<int>& pos, const Vector2D<int>& size, const PixelColor& c);