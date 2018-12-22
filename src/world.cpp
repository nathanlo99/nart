
#include "world.h"

std::pair<Color, std::vector<Ray>> World::intersect(const Ray &ray) const {
  return {Color{0, 0, 0}, std::vector<Ray>{}};
}
