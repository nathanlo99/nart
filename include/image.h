#ifndef IMAGE_H
#define IMAGE_H

#include "color.h"

#include <memory>

enum ImageFormat { BMP, JPG, PNG };
enum WrappingOption { REPEAT, MIRRORED_REPEAT, CLAMP_TO_EDGE, CLAMP_TO_BORDER };
enum FilterOption { NEAREST, LINEAR };

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

  Color at(float x, float y) const;
  Color &get(size_t x, size_t y) { return data[y * width + x]; }
  const Color &get(size_t x, size_t y) const { return data[y * width + x]; }
  void set(size_t x, size_t y, Color c) const { data[y * width + x] = c; }

  void write(ImageFormat format, const std::string &location);
};

#endif /* end of include guard: IMAGE_H */