
#include "image.h"

#include "common.h"

#include <cmath>
#include <fstream>
#include <string>
#include <vector>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

// TODO: Something is wrong with the BMP header, look into this at some point
void Image::write(ImageFormat format, const std::string &location) const {
  if (format == ImageFormat::JPG) {
  } else if (format == ImageFormat::PNG) {
  } else if (format == ImageFormat::BMP) {
    unsigned char *buf = static_cast<unsigned char *>(
        malloc(sizeof(unsigned char) * 3 * width * height));
    for (int i = 0; i < width * height; ++i) {
      buf[3 * i + 0] = static_cast<unsigned char>(floor(data[i].b * 255));
      buf[3 * i + 1] = static_cast<unsigned char>(floor(data[i].g * 255));
      buf[3 * i + 2] = static_cast<unsigned char>(floor(data[i].r * 255));
    }
    const std::string file_name = "output/" + location;
    stbi_flip_vertically_on_write(true); // First pixel is bottom left.
    const int result = stbi_write_bmp(file_name.c_str(), width, height, 3,
                                      static_cast<void *>(buf));
    free(buf);
    assert(result);
  }
}

Color Image::at(float x, float y) const {
  // TODO
  return Color{0, 0, 0};
}
