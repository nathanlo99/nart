
#include "objects/plane.h"

#include "common.h"

<<<<<<< HEAD
std::tuple<float, Color, vec3> Plane::intersect(const Ray &ray,
                                                float max_dist) const {
  const float vn = glm::dot(ray.direction, normal);
  if (fzero(vn))
    return no_hit;

  const float dist = glm::dot(point - ray.start, normal) / vn;
=======
std::tuple<float, vec3, vec3> Plane::intersect(const Ray &ray,
                                               float max_dist) const {
  const float vn = ray.direction.dot(normal);
  if (fzero(vn))
    return {-1, vec3(), {0, 0, 0}};

  const float dist = (point - ray.start).dot(normal) / vn;
>>>>>>> 997a69e30df785b8cd357e8ddfabc0c7ef7852a1
  if (dist > max_dist)
    return {-1, vec3(), {0, 0, 0}};

<<<<<<< HEAD
  const vec3 return_normal = glm::normalize(normal);
=======
  // This simulates a matte reflection!
  const vec3 dn = 0.00f * vec3{random<float>() - 0.5f, random<float>() - 0.5f,
                               random<float>() - 0.5f};
  const vec3 return_normal = (normal + dn).normalize();
>>>>>>> 997a69e30df785b8cd357e8ddfabc0c7ef7852a1
  return {dist, color, return_normal};
}

bool Plane::intersects(const Ray &ray, float min_dist, float max_dist) const {
<<<<<<< HEAD
  const float vn = glm::dot(ray.direction, normal);
  if (fzero(vn))
    return false;
  const float dist = glm::dot(point - ray.start, normal) / vn;
=======
  const float vn = ray.direction.dot(normal);
  if (fzero(vn))
    return false;
  const float dist = (point - ray.start).dot(normal) / vn;
>>>>>>> 997a69e30df785b8cd357e8ddfabc0c7ef7852a1
  return dist > min_dist && dist < max_dist;
}
