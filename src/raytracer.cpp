
#include "raytracer.h"

#include <cmath>

std::unique_ptr<Image> RayTracer::trace(const Camera &camera,
                                        const World &world) {
  const Vector3f &camera_position = camera.getP(), &forward = camera.getF(),
                 &right = camera.getR(), &up = camera.getU();
  const double space_width = 2 * tan(M_PI * horizontal_fov / 360.);
  const double pixel_size = space_width / screen_width;
  const Vector3f dx = pixel_size * right, dy = pixel_size * up;

  std::unique_ptr<Image> result =
      std::make_unique<Image>(screen_height, screen_width);
  for (size_t y = 0; y < screen_height; y++) {
    for (size_t x = 0; x < screen_width; x++) {
      Color result_color{0, 0, 0};
      for (size_t i = 0; i < aa_num; i++) {
        const float rx = random<float>(), ry = random<float>();
        const Vector3f dir = forward                               //
                             + (x - (screen_width / 2.) + rx) * dx //
                             + (y - (screen_height / 2.) + ry) * dy;
        const Ray ray{camera_position, dir.normalize()};
        const Color c = world.intersect(ray, max_depth);
        result_color = result_color + c;
      }
      result->set(x, y, result_color / aa_num);
    }
  }
  return result;
}
