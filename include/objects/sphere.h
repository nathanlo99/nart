#ifndef SPHERE_H
#define SPHERE_H

#include "color.h"
#include "objects/object.h"
#include "ray.h"
#include "vector3f.h"

class Sphere : public Object {
  Vector3f center;
  float radius;

public:
  Sphere(Vector3f center, float radius) : center{center}, radius{radius} {}
  ~Sphere() {}

  Color intersect(const Ray &ray) const override;
};

#endif
