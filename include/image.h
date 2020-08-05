
#pragma once

#include "common.h"

#include <memory>
#include <vector>

// Specifies the format to read/write an image from/to
enum ImageFormat { BMP, JPG, PNG };
// Specifies the texture wrapping option: these mirror OpenGL options
enum WrappingOption { REPEAT, MIRRORED_REPEAT, CLAMP_TO_EDGE, CLAMP_TO_BORDER };
// Specifies the interpolation strategy: these mirror OpenGL options
enum FilterOption { NEAREST, LINEAR };

// Stores a 2-dimensional pixel buffer, with arbitrary floating-point access
// method
class Image final {
  size_t height, width;
  std::vector<vec3> data;
  WrappingOption wrapping;
  FilterOption filter;

public:
  Image(const size_t height, const size_t width,
        WrappingOption wrapping = REPEAT, FilterOption filter = LINEAR)
      : height(height), width(width),
        data(height * width), wrapping{wrapping}, filter{filter} {}
  Image(ImageFormat format, const std::string &location);

  // Returns the color at the specified location, uses the wrapping and
  // interpolation strategies if the pixel is off-bounds or non-integral
  vec3 at(const float x, const float y) const;

  const vec3 get(const size_t x, const size_t y) const noexcept {
    return data[y * width + x];
  }
  void set(const size_t x, const size_t y, const vec3 &c) noexcept {
    data[y * width + x] = c;
  }

  // Writes the image to the specified location with the specified format, in a
  // relative path rooted at 'output'
  void write(ImageFormat format, const std::string &location) const;
};
