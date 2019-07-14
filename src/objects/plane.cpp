
#include "objects/plane.h"

#include "defs.h"

std::tuple<double, Color, Vector3f> Plane::intersect(const Ray &ray,
                                                     double max_dist) const {
  const double vn = ray.direction.dot(normal);
  if (fzero(vn))
    return {-1, Color::BLACK, {0, 0, 0}};
  // If the intersection point is behind the ray, this returns a negative
  // distance, which is handled correctly as a non-intersection by
  // Scene::intersect

  const double dist = (point - ray.start).dot(normal) / vn;
  if (dist > max_dist)
    return {-1, Color::BLACK, {0, 0, 0}};

  // This simulates a matte reflection!
  const Vector3f dn =
      0.00 * Vector3f{random<double>() - 0.5, random<double>() - 0.5,
                      random<double>() - 0.5};
  const Vector3f return_normal = (normal + dn).normalize();
  return {dist, color, return_normal};
}

bool Plane::intersects(const Ray &ray, double min_dist, double max_dist) const {
  const double vn = ray.direction.dot(normal);
  if (fzero(vn))
    return false;
  const double dist = (point - ray.start).dot(normal) / vn;
  return dist > min_dist && dist < max_dist;
}
