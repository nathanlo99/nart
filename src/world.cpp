
#include "world.h"

#include "defs.h"

Color World::intersect(const Ray &ray, size_t depth) const {
  if (objects.empty())
    return {0, 1, 0};
  const auto &tmp_result = objects[0]->intersect(ray);
  double dist = max_dist;
  Color result = background;
  if (tmp_result.first > 0) {
    dist = tmp_result.first;
    result = tmp_result.second;
  }
  for (const auto &x : objects) {
    const auto &tmp_result = x->intersect(ray);
    if (tmp_result.first > 0 && tmp_result.first < dist) {
      dist = tmp_result.first;
      result = tmp_result.second;
    }
  }
  return result;
}
