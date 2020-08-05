
#include "raytracer.h"

#include <cmath>

// TODO: toggle between random sampling and uniform square super-sampling
Image RayTracer::trace(const Camera &camera, const Scene &scene,
                       const std::string &render_name) {
  const vec3 &camera_position = camera.getP(), &forward = camera.getF(),
             &right = camera.getR(), &up = camera.getU();
<<<<<<< HEAD
  const float space_width = 2 * tan(M_PI * horizontal_fov / 360.);
=======
  const float space_width = 2.0f * tan(M_PI * horizontal_fov / 360.);
>>>>>>> 997a69e30df785b8cd357e8ddfabc0c7ef7852a1
  const float pixel_size = space_width / screen_width;
  const vec3 dx = pixel_size * right, dy = pixel_size * up;

  Image result{screen_height, screen_width};
  const size_t num_pixels = screen_height * screen_width;
  size_t num_processed = 0;
  auto last_ms = milli_time();

#pragma omp parallel for schedule(guided) collapse(2)
  for (size_t y = 0; y < screen_height; y++) {
    for (size_t x = 0; x < screen_width; x++) {
      vec3 result_color;
#pragma omp parallel for
      for (size_t i = 0; i < aa_num * aa_num; i++) {
<<<<<<< HEAD
        const float rx = (i / aa_num) / aa_num, ry = (i % aa_num) / aa_num;
        const vec3 dir = forward                                 //
                         + (x - (screen_width / 2.0f) + rx) * dx //
                         + (y - (screen_height / 2.0f) + ry) * dy;
        const Ray ray{camera_position, glm::normalize(dir)};
        const Color c = scene.intersect(ray, max_depth);
=======
        float rx = (i / aa_num) / aa_num, ry = (i % aa_num) / aa_num;
        // rx = random<float>(), ry = random<float>();
        const vec3 dir = forward                                 //
                         + (x - (screen_width / 2.0f) + rx) * dx //
                         + (y - (screen_height / 2.0f) + ry) * dy;
        const Ray ray{camera_position, dir.normalize()};
        const vec3 c = scene.intersect(ray, max_depth);
>>>>>>> 997a69e30df785b8cd357e8ddfabc0c7ef7852a1
        result_color = result_color + c;
      }
      result.set(x, y, result_color / (float)(aa_num * aa_num));

#pragma omp critical
      {
        num_processed++;
        const auto cur_ms = milli_time();
        if (cur_ms - last_ms > 1000) {
          last_ms = cur_ms;
          const float percent = num_processed * 100. / num_pixels;
          INFO("Completed " + std::to_string(percent) + "% of " + render_name);
          result.write(ImageFormat::BMP, "tmp/progress.bmp");
        }
      }
    }
  }
  result.write(ImageFormat::BMP, "tmp/progress.bmp");
  return result;
}
