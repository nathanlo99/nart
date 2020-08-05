
#pragma once

#include "objects/object.h"
#include "ray.h"

// A 3D sphere with a uniform color.
class Sphere : public Object {
  vec3 center;
  float radius;
  vec3 color;

public:
  Sphere(const vec3 &center, float radius, Color color)
      : center{center}, radius{radius}, color{color} {}
  ~Sphere() {}

  bool intersects(const Ray &ray, float min_dist,
                  float max_dist) const override;
  std::tuple<float, Color, vec3> intersect(const Ray &ray,
                                           float max_dist) const override;
};
