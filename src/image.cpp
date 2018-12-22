
#include "image.h"

#include "defs.h"

#include <fstream>
#include <string>

void Image::write(ImageFormat format, const std::string &location) {
  // std::ofstream out_file{"output/" + location};
  switch (format) {
  case ImageFormat::JPG:
    INFO("Saving image to " + location + " as JPG");
    break;
  case ImageFormat::PNG:
    INFO("Saving image to " + location + " as PNG");
    break;
  case ImageFormat::BMP:
    INFO("Saving image to " + location + " as BMP");
    break;
  default:
    break;
  }
}
