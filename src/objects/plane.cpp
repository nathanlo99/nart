
#include "objects/plane.h"

#include "defs.h"
std::pair<double, Color> Plane::intersect(const Ray &ray) const {
  const double vn = ray.direction.dot(normal);
  if (fzero(vn))
    return {-1, Color::BLACK};
  // std::cout << vn << std::endl;
  return {(point - ray.start).dot(normal) / vn, color};
}
