
#include "image.h"

#include "defs.h"
#include <string>

void Image::writeToFile(ImageFormat format, const std::string &location) {
  switch (format) {
  case ImageFormat::JPG:
    INFO << "Loading image " + location + " as JPG" << std::endl;
    break;
  case ImageFormat::PNG:
    INFO << "Loading image " + location + " as PNG" << std::endl;
    break;
  case ImageFormat::BMP:
    INFO << "Loading image " + location + " as BMP" << std::endl;
    break;
  default:
    throw std::exception{};
    break;
  }
}
