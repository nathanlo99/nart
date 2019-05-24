#ifndef IMAGE_H
#define IMAGE_H

#include "color.h"
#include <memory>

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
  std::unique_ptr<Color[]> data;
  WrappingOption wrapping;
  FilterOption filter;

public:
  Image(size_t height, size_t width, //
        WrappingOption wrapping = REPEAT, FilterOption filter = LINEAR)
      : height{height}, width{width},                    //
        data{std::make_unique<Color[]>(height * width)}, //
        wrapping{wrapping}, filter{filter} {}
  Image(ImageFormat format, const std::string &location);

  // Returns the color at the specified location, uses the wrapping and
  // interpolation strategies if the pixel is off-bounds or non-integral
  Color at(float x, float y) const;

  Color &get(size_t x, size_t y) noexcept { return data[y * width + x]; }
  const Color &get(size_t x, size_t y) const noexcept {
    return data[y * width + x];
  }
  void set(size_t x, size_t y, Color c) const noexcept {
    data[y * width + x] = c;
  }

  // Writes the image to the specified location with the specified format, in a
  // relative path rooted at 'output'
  void write(ImageFormat format, const std::string &location) const;
};

#endif /* end of include guard: IMAGE_H */
