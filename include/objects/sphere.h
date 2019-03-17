#ifndef SPHERE_H
#define SPHERE_H

#include "color.h"
#include "objects/object.h"
#include "ray.h"
#include "vector3f.h"

// A 3D sphere with a uniform color.
class Sphere : public Object {
  Vector3f center;
  float radius;
  Color color;

public:
  Sphere(const Vector3f &center, float radius, Color color)
      : center{center}, radius{radius}, color{color} {}
  ~Sphere() {}

  bool intersects(const Ray &ray, double min_dist,
                  double max_dist) const override;
  std::tuple<double, Color, Vector3f> intersect(const Ray &ray,
                                                double max_dist) const override;
};

#endif
