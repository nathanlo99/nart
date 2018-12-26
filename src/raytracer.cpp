
#include "raytracer.h"

#include <cmath>

Color getColor(const Ray &ray, const World &world, size_t depth) {
  return {1, 1, 1};
}

std::unique_ptr<Image> RayTracer::trace(const Camera &camera,
                                        const World &world) {
  const Vector3f camera_position = camera.getP(), forward = camera.getF(),
                 right = camera.getR(), up = camera.getU();
  const Vector3f::type pixel_size =
      sin(M_PI * horizontal_fov / 360.) / screen_width;
  const Vector3f dx = pixel_size * right, dy = pixel_size * up;
  const Vector3f bottom_left =
      forward - (screen_width / 2.) * dx - (screen_height / 2.) * dy;

  std::unique_ptr<Image> result =
      std::make_unique<Image>(screen_height, screen_width);
  for (size_t y = 0; y < screen_height; y++) {
    for (size_t x = 0; x < screen_width; x++) {
      const Ray ray{camera_position, bottom_left + x * dx + y * dy};
      result->set(x, y, getColor(ray, world, max_depth));
    }
  }
  return result;
}
