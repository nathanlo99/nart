
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
      const Vector3f dir = forward                                //
                           + (x - (screen_width / 2.) + 0.5) * dx //
                           + (y - (screen_height / 2.) + 0.5) * dy;
      const Ray ray{camera_position, dir.normalize()};
      const Color c = world.intersect(ray, max_depth);
      result->set(x, y, c);
    }
  }
  return result;
}
