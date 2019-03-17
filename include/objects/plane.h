#ifndef PLANE_H
#define PLANE_H

#include "objects/object.h"

// An infinite plane in 3D, with a uniform color.
class Plane : public Object {
  // A single point on the plane, and any normalized normal vector
  Vector3f point, normal;
  Color color;

public:
  Plane(const Vector3f &point, const Vector3f &normal, const Color &color)
      : point{point}, normal{normal.normalize()}, color{color} {}
  ~Plane() {}

  bool intersects(const Ray &ray, double min_dist,
                  double max_dist) const override;
  std::tuple<double, Color, Vector3f> intersect(const Ray &ray,
                                                double max_dist) const override;
};

#endif /* end of include guard: PLANE_H */
