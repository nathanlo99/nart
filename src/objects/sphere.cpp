
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
  if (t <= 0)
    return {-1, {0, 0, 0}, {0, 0, 0}};
  const double tt = sqrt(t), t1 = -tt - b;
  if (-tt > b) {
    return std::make_tuple(t1, color, (d + t1 * ray.direction).normalize());
  } else {
    return std::make_tuple(tt - b, color,
                           (d + (tt - b) * ray.direction).normalize());
  }
}

bool Sphere::intersects(const Ray &ray, double min_dist,
                        double max_dist) const {
  const Vector3f d = ray.start - center;
  const double b = d.dot(ray.direction);
  const double c = d.dot(d) - radius * radius;
  return b * b - c > min_dist && b * b - c < max_dist;
}
