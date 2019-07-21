
#ifndef RAYTRACER_H
#define RAYTRACER_H

#include "renderer.h"
#include "camera.h"
#include "image.h"
#include "world.h"

#include <memory>
#include <string>

class World;

// Object which, given a world and a camera, traces the scene into an image
class RayTracer : public Renderer {
  // Maximum recursive depth, for reflection ray-casts
  size_t max_depth = 10;
  // We super-sample each pixel in a square with aa_num points and average them
  size_t aa_num = 1;

public:
  RayTracer() noexcept {} // take defaults
  RayTracer(size_t screen_width, size_t screen_height,
            float horizontal_fov) noexcept
      : screen_width{screen_width}, screen_height{screen_height},
        horizontal_fov{horizontal_fov} {}
  ~RayTracer() noexcept {}

  // Traces the scene in 'world' as viewed by 'camera' and returns the result as
  // an Image
  Image trace(const Camera &camera, const World &world,
              const std::string &render_name);
};

#endif
