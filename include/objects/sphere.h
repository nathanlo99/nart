#ifndef SPHERE_H
#define SPHERE_H

#include "color.h"
#include "objects/object.h"
#include "ray.h"


// A 3D sphere with a uniform color.
class Sphere : public Object {
  vec3 center;
  float radius;
  Color color;

public:
  Sphere(const vec3 &center, float radius, Color color)
      : center{center}, radius{radius}, color{color} {}
  ~Sphere() {}

  bool intersects(const Ray &ray, float min_dist,
                  float max_dist) const override;
  std::tuple<float, Color, vec3> intersect(const Ray &ray,
                                                float max_dist) const override;
};

#endif
