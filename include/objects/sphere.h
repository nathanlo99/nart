
#pragma once

#include "objects/object.h"
#include "ray.h"
#include "vector3.h"

// A 3D sphere with a uniform color.
class Sphere : public Object {
  vec3 center;
  float radius;
  vec3 color;

public:
  Sphere(const vec3 &center, float radius, vec3 color)
      : center{center}, radius{radius}, color{color} {}
  ~Sphere() {}

  bool intersects(const Ray &ray, float min_dist,
                  float max_dist) const override;
  std::tuple<float, vec3, vec3> intersect(const Ray &ray,
                                          float max_dist) const override;
};
