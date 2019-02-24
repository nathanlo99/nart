
#include "objects/sphere.h"

#include "color.h"
#include "defs.h"
#include "ray.h"
#include "vector3f.h"

#include <utility>
#include <vector>

std::tuple<double, Color, Vector3f> Sphere::intersect(const Ray &ray) const {
  const Vector3f d = ray.start - center;
  const double b = d.dot(ray.direction);
  const double c = d.dot(d) - radius * radius;
  const double t = b * b - c;
  if (t <= 0)
    return {-1, {0, 0, 0}, {0, 0, 0}};
  const double tt = sqrt(t), t1 = -tt - b;
  if (-tt > b) {
    // return std::make_tuple(t1, color, Vector3f{0, 0, 1});
    return std::make_tuple(
        t1, color, (ray.start + (t1 * ray.direction) - center).normalize());
  } else {
    // return std::make_tuple(tt - b, color, Vector3f{0, 0, 1});
    return std::make_tuple(
        tt - b, color,
        (ray.start + ((tt - b) * ray.direction) - center).normalize());
  }
}
