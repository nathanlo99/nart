
#include "defs.h"

#include "camera.h"
#include "image.h"
#include "lights/point_light.h"
#include "objects/model.h"
#include "objects/plane.h"
#include "objects/sphere.h"
#include "raytracer.h"
#include "vector3f.h"
#include "world.h"

#include <ctime>
#include <iostream>

int main() {
  // const std::string log_name =
  //     "logs/log_" + std::to_string(static_cast<long>(std::time(0))) + ".txt";
  // const bool stdout_redirected = freopen(log_name.c_str(), "w", stdout);
  INFO("Starting program");

  World world;
  // world.addObject(std::make_unique<Sphere>(Vector3f{0, 0, 0}, 1,
  // Color::RED));
  // world.addObject(
  //     std::make_unique<Sphere>(Vector3f{1, 0, 0}, 0.5, Color::WHITE));
  // world.addObject(
  //     std::make_unique<Sphere>(Vector3f{1, 1, 0}, 0.5, Color::WHITE));
  // world.addObject(
  //     std::make_unique<Sphere>(Vector3f{0, 1, 0}, 0.5, Color::YELLOW));
  // world.addObject(
  //     std::make_unique<Sphere>(Vector3f{0, -1, 0}, 0.25, Color::GREEN));
  // world.addObject(std::make_unique<Plane>(Vector3f{0, 0, -4}, Vector3f{0, 0,
  // 1}, 0.3 * Color::WHITE));

  world.addObject(std::make_unique<Model>("monkey", ModelTraits::OBJ));
  // world.addObject(std::make_unique<Model>("sasuke", ModelTraits::MODEL));

  RayTracer ray_tracer{480, 300, 60};
  const double distance = 4;
  world.addLight(std::make_unique<PointLight>(Vector3f{distance, 0, distance},
                                              0.3 * Color::WHITE));
  world.addLight(std::make_unique<PointLight>(Vector3f{0, distance, distance},
                                              0.3 * Color::RED));
  world.addLight(std::make_unique<PointLight>(Vector3f{-distance, 0, distance},
                                              0.3 * Color::BLUE));
  world.addLight(std::make_unique<PointLight>(Vector3f{0, -distance, distance},
                                              0.3 * Color::GREEN));

  for (int i = 0; i < 360; ++i) {
    Vector3f camera_loc{distance * cos(M_PI * i / 180.),
                        distance * sin(M_PI * i / 180.), distance / 3.},
        look_at{0, 0, 0};
    Camera camera{camera_loc, look_at};
    std::unique_ptr<Image> ray_trace_output = ray_tracer.trace(camera, world);
    std::stringstream ss;
    ss << "animate/frame_" << std::setw(3) << std::setfill('0') << i << ".bmp";
    ray_trace_output->write(ImageFormat::BMP, ss.str());
    INFO("Wrote " + ss.str());
  }

  INFO("Terminating program");
  // if (stdout_redirected)
  //   fclose(stdout);
  // INFO("Log at " + log_name);
  return 0;
}
