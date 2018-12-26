
#include "defs.h"

#include "camera.h"
#include "image.h"
#include "objects/model.h"
#include "objects/sphere.h"
#include "raytracer.h"
#include "vector3f.h"
#include "world.h"

#include <ctime>
#include <iostream>

int main() {
  const std::string log_name =
      "logs/log_" + std::to_string(static_cast<long>(std::time(0))) + ".txt";
  const bool stdout_redirected = freopen(log_name.c_str(), "w", stdout);
  INFO("Starting program");

  Vector3f camera_loc{0, 0, 0}, look_at{1, 1, 1};
  Camera camera{camera_loc, look_at};

  World world;
  world.addObject(std::make_unique<Sphere>(Vector3f{1, 1, 1}, 3));
  world.addObject(std::make_unique<Model>("cow", ModelTraits::OBJ));
  world.addObject(std::make_unique<Model>("sasuke", ModelTraits::MODEL));

  RayTracer ray_tracer; // Default resolution and FOV

  std::unique_ptr<Image> ray_trace_output = ray_tracer.trace(camera, world);
  ray_trace_output->write(ImageFormat::BMP, "test.bmp");

  INFO("Terminating program");
  if (stdout_redirected)
    fclose(stdout);
  INFO("Log at " + log_name);
  return 0;
}
