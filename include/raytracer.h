
#ifndef RAYTRACER_H
#define RAYTRACER_H

#include "camera.h"
#include "image.h"
#include "world.h"

#include <memory>
#include <string>

class World;

class RayTracer {
  // Screen width and height in pixels
  size_t screen_width = 320, screen_height = 200;
  // Horizontal field of view, in degrees
  double horizontal_fov = 60;
  size_t max_depth = 5;

public:
  RayTracer() {} // take defaults
  RayTracer(size_t screen_width, size_t screen_height, float horizontal_fov)
      : screen_width{screen_width}, screen_height{screen_height},
        horizontal_fov{horizontal_fov} {}
  ~RayTracer() {}

  std::unique_ptr<Image> trace(const Camera &camera, const World &world);
};

#endif
