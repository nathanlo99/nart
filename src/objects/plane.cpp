
#include "objects/plane.h"

#include "defs.h"

std::tuple<double, Color, Vector3f> Plane::intersect(const Ray &ray,
                                                     double max_dist) const {
  const double vn = ray.direction.dot(normal);
  if (fzero(vn))
    return {-1, Color::BLACK, {0, 0, 0}};
  return {(point - ray.start).dot(normal) / vn, color, normal};
}

bool Plane::intersects(const Ray &ray, double max_dist) const {
  const double vn = ray.direction.dot(normal);
  if (fzero(vn))
    return false;
  const double dist = (point - ray.start).dot(normal) / vn;
  return dist > accuracy && dist < max_dist;
}
