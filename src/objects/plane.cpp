
#include "objects/plane.h"

#include "defs.h"

std::tuple<float, vec3, vec3> Plane::intersect(const Ray &ray,
                                               float max_dist) const {
  const float vn = ray.direction.dot(normal);
  if (fzero(vn))
    return {-1, vec3(), {0, 0, 0}};

  const float dist = (point - ray.start).dot(normal) / vn;
  if (dist > max_dist)
    return {-1, vec3(), {0, 0, 0}};

  // This simulates a matte reflection!
  const vec3 dn = 0.00f * vec3{random<float>() - 0.5f, random<float>() - 0.5f,
                               random<float>() - 0.5f};
  const vec3 return_normal = (normal + dn).normalize();
  return {dist, color, return_normal};
}

bool Plane::intersects(const Ray &ray, float min_dist, float max_dist) const {
  const float vn = ray.direction.dot(normal);
  if (fzero(vn))
    return false;
  const float dist = (point - ray.start).dot(normal) / vn;
  return dist > min_dist && dist < max_dist;
}
