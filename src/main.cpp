
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
  // Color::RED)); world.addObject(
  //     std::make_unique<Sphere>(Vector3f{1, 0, 0}, 0.5, Color::WHITE));
  // world.addObject(
  //     std::make_unique<Sphere>(Vector3f{1, 1, 0}, 0.5, Color::WHITE));
  // world.addObject(
  //     std::make_unique<Sphere>(Vector3f{0, 1, 0}, 0.5, Color::YELLOW));
  // world.addObject(
  //     std::make_unique<Sphere>(Vector3f{0, -1, 0}, 0.25, Color::GREEN));
  world.addObject(std::make_unique<Plane>(Vector3f{0, 0, 0}, Vector3f{0, 0, 1},
                                          0.3 * Color::BLACK));

  world.addObject(std::make_unique<Model>("cow", ModelTraits::OBJ));
  // world.addObject(std::make_unique<Model>("sasuke", ModelTraits::MODEL));

  // RayTracer ray_tracer{1680, 1050, 60};
  RayTracer ray_tracer{800, 500, 60};
  // RayTracer ray_tracer{300, 200, 60};
  const double distance = 3, height_offset = 0;
  world.addLight(std::make_unique<PointLight>(Vector3f{distance, 0, distance},
                                              0.3 * Color::WHITE));
  world.addLight(std::make_unique<PointLight>(Vector3f{0, distance, distance},
                                              0.3 * Color::RED));
  world.addLight(std::make_unique<PointLight>(Vector3f{-distance, 0, distance},
                                              0.3 * Color::BLUE));
  world.addLight(std::make_unique<PointLight>(Vector3f{0, -distance, distance},
                                              0.3 * Color::GREEN));

  for (int i = 0; i < 360; ++i) {
    const auto frame_start = milli_time();
    std::stringstream ss;
    ss << "animate/frame_" << std::setw(3) << std::setfill('0') << i << ".bmp";
    const std::string file_name = ss.str();

    const Vector3f camera_loc{distance * sin(M_PI * i / 180.),
                              distance * cos(M_PI * i / 180.),
                              distance / 3. + height_offset};
    const Vector3f look_at{0, 0, height_offset};

    const Camera camera{camera_loc, look_at};
    std::unique_ptr<Image> ray_trace_output =
        ray_tracer.trace(camera, world, file_name);
    ray_trace_output->write(ImageFormat::BMP, file_name);
    const auto frame_ms = milli_time() - frame_start;
    INFO("Wrote " + ss.str() + " in " + std::to_string(frame_ms / 1000) + "s");
  }

  INFO("Terminating program");
  // if (stdout_redirected)
  //   fclose(stdout);
  // INFO("Log at " + log_name);
  return 0;
}
