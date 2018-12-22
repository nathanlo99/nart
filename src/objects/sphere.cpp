
#include "objects/sphere.h"

#include "color.h"
#include "ray.h"
#include <utility>
#include <vector>

std::pair<Color, std::vector<Ray>> Sphere::intersect(Ray ray) const {
  return {Color{0, 0, 0}, std::vector<Ray>{}};
}
