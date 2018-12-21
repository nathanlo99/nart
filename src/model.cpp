
#include "model.h"

#include "color.h"
#include "defs.h"
#include "ray.h"

#include <utility>
#include <vector>

Model::Model(const std::string &name, ModelTraits option = ModelTraits::MODEL) {
  //
  INFO << "Loading model " + name << std::endl;
}

std::pair<Color, std::vector<Ray>> Model::intersect(Ray ray) const {
  return {Color{0, 0, 0}, std::vector<Ray>{}};
}
