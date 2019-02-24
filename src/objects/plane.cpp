
#include "objects/plane.h"

#include "defs.h"
std::tuple<double, Color, Vector3f> Plane::intersect(const Ray &ray) const {
  const double vn = ray.direction.dot(normal);
  if (fzero(vn))
    return {-1, Color::BLACK, {0, 0, 0}};
  return {(point - ray.start).dot(normal) / vn, color, normal};
}
