
#include "objects/sphere.h"

#include "color.h"
#include "defs.h"
#include "ray.h"
#include "vector3f.h"

#include <utility>
#include <vector>

std::tuple<double, Color, Vector3f> Sphere::intersect(const Ray &ray,
                                                      double max_dist) const {
  const Vector3f d = ray.start - center;
  const double b = d.dot(ray.direction);
  const double c = d.dot(d) - radius * radius;
  const double t = b * b - c;
  if (t < accuracy)
    return {-1, {0, 0, 0}, {0, 0, 0}};
  const double disc = sqrt(t), t1 = -b - disc, t2 = -b + disc;
  if (t1 > 0) {
    return std::make_tuple(t1, color, (d + t1 * ray.direction).normalize());
  } else if (t2 > 0) {
    return std::make_tuple(t2, color, (d + t2 * ray.direction).normalize());
  } else {
    return {-1, {0, 0, 0}, {0, 0, 0}};
  }
}

bool Sphere::intersects(const Ray &ray, double min_dist,
                        double max_dist) const {
  const Vector3f d = ray.start - center;
  const double b = d.dot(ray.direction);
  const double c = d.dot(d) - radius * radius;
  const double discr = b * b - c;
  if (discr < 0)
    return false;
  const double tt = sqrt(discr), t1 = -b - tt, t2 = -b + tt;
  return (t1 > min_dist && t1 < max_dist) || (t2 > min_dist && t2 < max_dist);
}
