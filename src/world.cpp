
#include "world.h"

#include "defs.h"

Color World::intersect(const Ray &ray, size_t depth) const {
  if (objects.empty())
    return {0, 1, 0};
  double dist = 10000, tmp_dist;
  Color result, cur_color;
  std::tie(tmp_dist, cur_color) = objects[0]->intersect(ray);
  if (tmp_dist >= accuracy) {
    dist = tmp_dist;
    result = cur_color;
  }
  for (const auto &x : objects) {
    std::tie(tmp_dist, cur_color) = x->intersect(ray);
    if (tmp_dist >= accuracy && tmp_dist < dist) {
      dist = tmp_dist;
      result = cur_color;
    }
  }
  return result;
}
