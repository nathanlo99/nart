
#include <benchmark/benchmark.h>

#include <vector>

#include "camera.h"
#include "defs.h"
#include "image.h"
#include "lights/point_light.h"
#include "objects/model.h"
#include "objects/sphere.h"
#include "raytracer.h"
#include "vector3.h"
#include "scene.h"

static void bench_trace(benchmark::State &state) {
  vec3 camera_loc{3, 1.5, -4}, look_at{0, 0, 0};
  Camera camera{camera_loc, look_at};

  scene scene;
  scene.addObject(std::make_unique<Sphere>(vec3{0, 0, 0}, 1, vec3(1.0, 0.0, 0.0)));
  scene.addObject(
      std::make_unique<Sphere>(vec3{0, 1, 0}, 0.5, vec3(0.0, 1.0, 0.0)));
  scene.addObject(std::make_unique<Sphere>(vec3{0, -1, 0}, 1, vec3(0.0, 0.0, 1.0)));
  scene.addLight(std::make_unique<PointLight>(vec3{2, 2, 2}, vec3(1.0, 1.0, 1.0)));

  RayTracer ray_tracer{640, 400, 60};

  std::unique_ptr<Image> ray_trace_output;
  for (auto _ : state) {
    ray_trace_output = ray_tracer.trace(camera, scene);
  }
  ray_trace_output->write(ImageFormat::BMP, "benchmark.bmp");
}

static void bench_image_write(benchmark::State &state) {
  std::unique_ptr<Image> image = std::make_unique<Image>(1000, 1000);
  for (auto _ : state) {
    image->write(ImageFormat::BMP, "benchmark_empty.bmp");
  }
}

BENCHMARK(bench_trace);
BENCHMARK(bench_image_write);

BENCHMARK_MAIN();
