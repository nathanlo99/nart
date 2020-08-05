#ifndef PLANE_H
#define PLANE_H

#include "objects/object.h"

// An infinite plane in 3D, with a uniform color.
class Plane : public Object {
  // A single point on the plane, and any normalized normal vector
  vec3 point, normal;
  Color color;

public:
  Plane(const vec3 &point, const vec3 &normal, const Color &color)
      : point{point}, normal{glm::normalize(normal)}, color{color} {}
  ~Plane() {}

  bool intersects(const Ray &ray, float min_dist,
                  float max_dist) const override;
  std::tuple<float, Color, vec3> intersect(const Ray &ray,
                                           float max_dist) const override;
};

#endif /* end of include guard: PLANE_H */
