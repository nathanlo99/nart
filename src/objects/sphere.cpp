
#include "objects/sphere.h"

#include "color.h"
#include "defs.h"
#include "ray.h"

#include <utility>
#include <vector>

std::pair<double, Color> Sphere::intersect(const Ray &ray) const {
  Vector3f d = ray.start - center;
  double b = d.dot(ray.direction);
  double c = d.dot(d) - radius * radius;
  if (b * b < c)
    return {-1, Color{0, 1, 0}};
  double t1 = -sqrt(b * b - c) - b;
  return (t1 > 0) ? std::make_pair(t1, color)
                  : std::make_pair(-t1 - 2 * b, color);
}
