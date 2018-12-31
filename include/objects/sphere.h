#ifndef SPHERE_H
#define SPHERE_H

#include "color.h"
#include "objects/object.h"
#include "ray.h"
#include "vector3f.h"

class Sphere : public Object {
  Vector3f center;
  float radius;
  Color color;

public:
  Sphere(const Vector3f &center, float radius, Color color)
      : center{center}, radius{radius}, color{color} {}
  ~Sphere() {}

  std::pair<double, Color> intersect(const Ray &ray) const override;
};

#endif
