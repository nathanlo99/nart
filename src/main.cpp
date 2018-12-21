
#include "defs.h"

#include "camera.h"
#include "image.h"
#include "model.h"
#include "raytracer.h"
#include "sphere.h"
#include "vector3f.h"
#include "world.h"

#include <ctime>
#include <iostream>

int main() {
  // Redirect stdout to log file (temporary)
  const std::string log_name =
      "logs/log_" + std::to_string(static_cast<long>(std::time(0))) + ".txt";
  freopen(log_name.c_str(), "w", stdout);

  INFO << "Starting program" << std::endl;

  Vector3f camera_loc{0, 0, 0}, look_at{1, 1, 1};
  Camera camera{camera_loc, look_at};

  World world;
  world.addObject(std::make_unique<Sphere>(Vector3f{1, 1, 1}, 3));
  world.addObject(std::make_unique<Model>("cow", ModelTraits::OBJ));
  world.addObject(std::make_unique<Model>("sasuke", ModelTraits::MODEL));

  RayTracer ray_tracer; // Default resolution and FOV

  std::unique_ptr<Image> ray_trace_output = ray_tracer.trace(camera, world);
  ray_trace_output->writeToFile(ImageFormat::JPG, "test.jpg");

  INFO << "Terminating program" << std::endl;
  fclose(stdout);
  INFO << "Log at " << log_name << std::endl;
  return 0;
}
