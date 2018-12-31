
#include "world.h"

#include "defs.h"

Color World::intersect(const Ray &ray, size_t depth) const {
  if (objects.empty())
    return {0, 1, 0};
  double dist = 10000;
  const auto &tmp_result = objects[0]->intersect(ray);
  Color result;
  if (tmp_result.first >= accuracy) {
    dist = tmp_result.first;
    result = tmp_result.second;
  }
  for (const auto &x : objects) {
    const auto &tmp_result = x->intersect(ray); // dist, color
    if (tmp_result.first >= accuracy && tmp_result.first < dist) {
      dist = tmp_result.first;
      result = tmp_result.second;
    }
  }
  return result;
}
