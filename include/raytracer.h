
#pragma once

#include "camera.h"
#include "image.h"
#include "scene.h"

#include <memory>
#include <string>

class Scene;

// Object which, given a scene and a camera, traces the scene into an image
class RayTracer {
  // Screen width and height in pixels
  size_t screen_width = 320, screen_height = 200;
  // Horizontal field of view, in degrees
  float horizontal_fov = 60;
  // Maximum recursive depth, for reflection ray-casts
  size_t max_depth = 100;
  // We super-sample each pixel in a square with aa_num points and average them
  size_t aa_num = 1;

public:
  RayTracer() noexcept {} // take defaults
  RayTracer(size_t screen_width, size_t screen_height,
            float horizontal_fov) noexcept
      : screen_width{screen_width}, screen_height{screen_height},
        horizontal_fov{horizontal_fov} {}
  ~RayTracer() noexcept {}

  // Traces the scene in 'scene' as viewed by 'camera' and returns the result as
  // an Image
  Image trace(const Camera &camera, const Scene &scene,
              const std::string &render_name);
};
