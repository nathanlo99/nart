
#include "objects/model.h"

#include "color.h"
#include "defs.h"
#include "ray.h"

#include <utility>
#include <vector>

Model::Model(const std::string &name, ModelTraits option) {
  INFO("Loading model " + name);
}

Color Model::intersect(const Ray &ray) const { return {0, 0, 0}; }
