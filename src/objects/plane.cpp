
#include "objects/plane.h"

#include "common.h"

std::tuple<float, Color, vec3> Plane::intersect(const Ray &ray,
                                                float max_dist) const {
  const float vn = glm::dot(ray.direction, normal);
  if (fzero(vn))
    return no_hit;

  const float dist = glm::dot(point - ray.start, normal) / vn;
  if (dist > max_dist)
    return {-1, Color::BLACK, {0, 0, 0}};

  const vec3 return_normal = glm::normalize(normal);
  return {dist, color, return_normal};
}

bool Plane::intersects(const Ray &ray, float min_dist, float max_dist) const {
  const float vn = glm::dot(ray.direction, normal);
  if (fzero(vn))
    return false;
  const float dist = glm::dot(point - ray.start, normal) / vn;
  return dist > min_dist && dist < max_dist;
}
