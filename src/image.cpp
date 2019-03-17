
#include "image.h"

#include "defs.h"

#include <cmath>
#include <fstream>
#include <string>
#include <vector>

// TODO: Something is wrong with the BMP header, look into this at some point
void Image::write(ImageFormat format, const std::string &location) const {
  if (format == ImageFormat::JPG) {
  } else if (format == ImageFormat::PNG) {
  } else if (format == ImageFormat::BMP) {
    std::ofstream out_file{"output/" + location, std::ofstream::binary};
    const size_t size_bytes = 3 * width * height;
    const size_t file_size = 14 + 40 + size_bytes;

    const int ppm = 2808;
    unsigned char bmp_header[14] = {'B', 'M', 0, 0, 0, 0, 54, 0, 0, 0};
    unsigned char dib_header[40] = {40, 0, 0, 0, 0, 0, 0,  0,
                                    0,  0, 0, 0, 1, 0, 24, 0};
    bmp_header[2] = static_cast<unsigned char>(file_size);
    bmp_header[3] = static_cast<unsigned char>(file_size >> 8);
    bmp_header[4] = static_cast<unsigned char>(file_size >> 16);
    bmp_header[5] = static_cast<unsigned char>(file_size >> 24);

    dib_header[4] = static_cast<unsigned char>(width);
    dib_header[5] = static_cast<unsigned char>(width >> 8);
    dib_header[6] = static_cast<unsigned char>(width >> 16);
    dib_header[7] = static_cast<unsigned char>(width >> 24);

    dib_header[8] = static_cast<unsigned char>(height);
    dib_header[9] = static_cast<unsigned char>(height >> 8);
    dib_header[10] = static_cast<unsigned char>(height >> 16);
    dib_header[11] = static_cast<unsigned char>(height >> 24);

    dib_header[25] = static_cast<unsigned char>(ppm);
    dib_header[26] = static_cast<unsigned char>(ppm >> 8);
    dib_header[27] = static_cast<unsigned char>(ppm >> 16);
    dib_header[28] = static_cast<unsigned char>(ppm >> 24);

    out_file.write(reinterpret_cast<char *>(bmp_header), 14);
    out_file.write(reinterpret_cast<char *>(dib_header), 40);

    std::vector<unsigned char> buf(3 * width * height);
    const char *signed_buf = reinterpret_cast<const char *>(&buf[0]);
#pragma omp parallel for ordered
    for (size_t i = 0; i < width * height; ++i) {
      buf[3 * i + 0] = static_cast<unsigned char>(floor(data[i].b * 255));
      buf[3 * i + 1] = static_cast<unsigned char>(floor(data[i].g * 255));
      buf[3 * i + 2] = static_cast<unsigned char>(floor(data[i].r * 255));
    }
    out_file.write(signed_buf, 3L * width * height);
  }
}

Color Image::at(float x, float y) const {
  // TODO
  return Color{0, 0, 0};
}
