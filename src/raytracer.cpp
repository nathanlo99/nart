
#include "raytracer.h"

#include <cmath>

std::unique_ptr<Image> RayTracer::trace(const Camera &camera,
                                        const World &world,
                                        const std::string &render_name) {
  const Vector3f &camera_position = camera.getP(), &forward = camera.getF(),
                 &right = camera.getR(), &up = camera.getU();
  const double space_width = 2 * tan(M_PI * horizontal_fov / 360.);
  const double pixel_size = space_width / screen_width;
  const Vector3f dx = pixel_size * right, dy = pixel_size * up;

  std::unique_ptr<Image> result =
      std::make_unique<Image>(screen_height, screen_width);
  const size_t num_pixels = screen_height * screen_width;
  size_t num_processed = 0;
  int percent = 0;
  auto last_ms = milli_time();

#pragma omp parallel for collapse(2)
  for (size_t y = 0; y < screen_height; y++) {
    for (size_t x = 0; x < screen_width; x++) {
      Color result_color{0, 0, 0};
#pragma omp parallel for
      for (size_t i = 0; i < aa_num * aa_num; i++) {
        const float rx = (double)(i / aa_num) / aa_num,
                    ry = (double)(i % aa_num) / aa_num;
        // rx = random<float>(), ry = random<float>();
        const Vector3f dir = forward                               //
                             + (x - (screen_width / 2.) + rx) * dx //
                             + (y - (screen_height / 2.) + ry) * dy;
        const Ray ray{camera_position, dir.normalize()};
        const Color c = world.intersect(ray, max_depth);
        result_color = result_color + c;
      }
      result->set(x, y, result_color / (float)(aa_num * aa_num));

#pragma omp critical
      {
        num_processed++;
        int new_percent = num_processed * 100 / num_pixels;

        if (new_percent != percent) {
          const auto cur_ms = milli_time();
          if (cur_ms - last_ms > 1000) {
            last_ms = cur_ms;
            INFO("Completed " + std::to_string(new_percent) + "% of " +
                 render_name);
            percent = new_percent;
            result->write(ImageFormat::BMP, "tmp/" + render_name);
          }
        }
      }
    }
  }
  result->write(ImageFormat::BMP, "tmp/" + render_name);
  return result;
}
