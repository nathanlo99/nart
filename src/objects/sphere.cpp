
#include "objects/sphere.h"

#include "defs.h"
#include "ray.h"
#include "vector3.h"

#include <utility>
#include <vector>

std::tuple<float, vec3, vec3> Sphere::intersect(const Ray &ray,
                                                float max_dist) const {
  const vec3 d = ray.start - center;
  const float b = d.dot(ray.direction);
  const float c = d.dot(d) - radius * radius;
  const float t = b * b - c;
  if (t < accuracy)
    return {-1, {0, 0, 0}, {0, 0, 0}};
  const float disc = sqrt(t), t1 = -b - disc, t2 = -b + disc;
  if (t1 > 0) {
    return std::make_tuple(t1, color, (d + t1 * ray.direction).normalize());
  } else if (t2 > 0) {
    return std::make_tuple(t2, color, (d + t2 * ray.direction).normalize());
  } else {
    return {-1, {0, 0, 0}, {0, 0, 0}};
  }
}

bool Sphere::intersects(const Ray &ray, float min_dist, float max_dist) const {
  const vec3 d = ray.start - center;
  const float b = d.dot(ray.direction);
  const float c = d.dot(d) - radius * radius;
  const float discr = b * b - c;
  if (discr < 0)
    return false;
  const float tt = sqrt(discr), t1 = -b - tt, t2 = -b + tt;
  return (t1 > min_dist && t1 < max_dist) || (t2 > min_dist && t2 < max_dist);
}
