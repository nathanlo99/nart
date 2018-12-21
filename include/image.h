#ifndef IMAGE_H
#define IMAGE_H

#include "color.h"

#include <memory>

enum ImageFormat { BMP, JPG, PNG };

// TODO
class Image {
  size_t height, width;
  std::unique_ptr<Color[]> data;

public:
  Image(size_t height, size_t width)
      : height{height}, width{width}, //
        data{std::make_unique<Color[]>(height * width)} {}
  ~Image() {}

  void writeToFile(ImageFormat format, const std::string &location);
};

#endif /* end of include guard: IMAGE_H */
