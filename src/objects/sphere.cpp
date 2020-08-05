
#include "objects/sphere.h"

#include "common.h"
#include "ray.h"

#include <utility>
#include <vector>

std::tuple<float, vec3, vec3> Sphere::intersect(const Ray &ray,
                                                float max_dist) const {
  const vec3 d = ray.start - center;
  const float b = glm::dot(d, ray.direction);
  const float c = glm::dot(d, d) - radius * radius;
  const float t = b * b - c;
  if (t < accuracy)
    return no_hit;
  const float disc = sqrt(t), t1 = -b - disc, t2 = -b + disc;
  if (t1 > 0) {
    return std::make_tuple(t1, colour, glm::normalize(d + t1 * ray.direction));
  } else if (t2 > 0) {
    return std::make_tuple(t2, colour, glm::normalize(d + t2 * ray.direction));
  } else {
    return no_hit;
  }
}

bool Sphere::intersects(const Ray &ray, float min_dist, float max_dist) const {
  const vec3 d = ray.start - center;
  const float b = glm::dot(d, ray.direction);
  const float c = glm::dot(d, d) - radius * radius;
  const float discr = b * b - c;
  if (discr < 0)
    return false;
  const float tt = sqrt(discr), t1 = -b - tt, t2 = -b + tt;
  return (t1 > min_dist && t1 < max_dist) || (t2 > min_dist && t2 < max_dist);
}
