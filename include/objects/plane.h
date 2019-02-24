#ifndef PLANE_H
#define PLANE_H

#include "objects/object.h"

class Plane : public Object {
  Vector3f point, normal;
  Color color;

public:
  Plane(const Vector3f &point, const Vector3f &normal, const Color &color)
      : point{point}, normal{normal.normalize()}, color{color} {}
  ~Plane() {}

  std::pair<double, Color> intersect(const Ray &ray) const override;
};

#endif /* end of include guard: PLANE_H */
