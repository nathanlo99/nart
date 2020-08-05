
#pragma once

#include "objects/object.h"
#include "ray.h"

// A 3D sphere with a uniform colour.
class Sphere : public Object {
  vec3 center;
  float radius;
  vec3 colour;

public:
  Sphere(const vec3 &center, float radius, vec3 colour)
      : center{center}, radius{radius}, colour(colour) {}
  ~Sphere() {}

  bool intersects(const Ray &ray, float min_dist,
                  float max_dist) const override;
  std::tuple<float, vec3, vec3> intersect(const Ray &ray,
                                          float max_dist) const override;
};
