
#include "defs.h"

#include "camera.h"
#include "image.h"
#include "lights/point_light.h"
#include "objects/model.h"
#include "objects/plane.h"
#include "objects/sphere.h"
#include "raytracer.h"
#include "scene.h"
#include "vector3f.h"

#include <ctime>
#include <iostream>

int main() {
  INFO("Starting program");

  Scene scene;

  // RayTracer ray_tracer{1680, 1050, 60};
  // RayTracer ray_tracer{1200, 900, 60};
  RayTracer ray_tracer{800, 500, 60};
  // RayTracer ray_tracer{500, 350, 60};
  const float distance = 5, height_offset = 0, wall_distance = distance * 1.005;

  // // Add all sorts of objects
  // scene.addObject(std::make_unique<Sphere>(Vector3f{0, 0, 0}, 1,
  // Color::RED)); scene.addObject(
  //     std::make_unique<Sphere>(Vector3f{1, 0, 0}, 0.5, Color::WHITE));
  // scene.addObject(
  //     std::make_unique<Sphere>(Vector3f{1, 1, 0}, 0.5, Color::WHITE));
  // scene.addObject(
  //     std::make_unique<Sphere>(Vector3f{0, 1, 0}, 0.5, Color::YELLOW));
  // scene.addObject(
  //     std::make_unique<Sphere>(Vector3f{0, -1, 0}, 0.25, Color::GREEN));

  scene.addObject(std::make_unique<Plane>(Vector3f{0, 0, -1}, Vector3f{0, 0, 1},
                                          Color::BLACK));
  scene.addObject(std::make_unique<Plane>(Vector3f{0, wall_distance, 0},
                                          Vector3f{0, -1, 0}, Color::BLACK));
  scene.addObject(std::make_unique<Plane>(Vector3f{wall_distance, 0, 0},
                                          Vector3f{-1, 0, 0}, Color::BLACK));
  scene.addObject(std::make_unique<Plane>(Vector3f{0, -wall_distance, 0},
                                          Vector3f{0, 1, 0}, Color::BLACK));
  scene.addObject(std::make_unique<Plane>(Vector3f{-wall_distance, 0, 0},
                                          Vector3f{1, 0, 0}, Color::BLACK));

  // scene.addObject(
  //     std::make_unique<Sphere>(Vector3f{wall_distance, wall_distance, 0},
  //                              wall_distance * 0.5, Color::WHITE));
  // scene.addObject(
  //     std::make_unique<Sphere>(Vector3f{-wall_distance, wall_distance, 0},
  //                              wall_distance * 0.5, Color::WHITE));
  // scene.addObject(
  //     std::make_unique<Sphere>(Vector3f{wall_distance, -wall_distance, 0},
  //                              wall_distance * 0.5, Color::WHITE));
  // scene.addObject(
  //     std::make_unique<Sphere>(Vector3f{-wall_distance, -wall_distance, 0},
  //                              wall_distance * 0.5, Color::WHITE));

  scene.addObject(std::make_unique<Model>("casting", ModelTraits::OBJ));
  // scene.addObject(std::make_unique<Model>("sasuke", ModelTraits::MODEL));

  // Let there be light!
  scene.addLight(std::make_unique<PointLight>(Vector3f{distance, 0, distance},
                                              0.3 * Color::WHITE));
  scene.addLight(std::make_unique<PointLight>(Vector3f{0, distance, distance},
                                              0.3 * Color::RED));
  scene.addLight(std::make_unique<PointLight>(Vector3f{-distance, 0, distance},
                                              0.3 * Color::BLUE));
  scene.addLight(std::make_unique<PointLight>(Vector3f{0, -distance, distance},
                                              0.3 * Color::GREEN));

  // Renders 360 frames of our scene in a rotating frame-of-reference
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
    const Image ray_trace_output = ray_tracer.trace(camera, scene, file_name);
    ray_trace_output.write(ImageFormat::BMP, file_name);
    const auto frame_ms = milli_time() - frame_start;
    INFO("Wrote " + ss.str() + " in " + std::to_string(frame_ms / 1000) + "s");
  }
}
