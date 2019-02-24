
#include <benchmark/benchmark.h>

#include <vector>

#include "camera.h"
#include "defs.h"
#include "image.h"
#include "objects/model.h"
#include "objects/sphere.h"
#include "raytracer.h"
#include "vector3f.h"
#include "world.h"

static void bench_trace(benchmark::State &state) {
  Vector3f camera_loc{3, 1.5, -4}, look_at{0, 0, 0};
  Camera camera{camera_loc, look_at};

  World world;
  world.addObject(std::make_unique<Sphere>(Vector3f{0, 0, 0}, 1, Color::RED));
  world.addObject(
      std::make_unique<Sphere>(Vector3f{0, 1, 0}, 0.5, Color::GREEN));
  world.addObject(std::make_unique<Sphere>(Vector3f{0, -1, 0}, 1, Color::BLUE));
  RayTracer ray_tracer{640, 400, 60};

  std::unique_ptr<Image> ray_trace_output;
  for (auto _ : state) {
    ray_trace_output = ray_tracer.trace(camera, world);
  }
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
