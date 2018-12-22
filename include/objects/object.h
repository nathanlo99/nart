#ifndef OBJECT_H
#define OBJECT_H

#include "color.h"
#include "ray.h"

#include <utility>
#include <vector>

class World;

class Object {
  World *world;

public:
  Object() {}
  virtual ~Object() {}

  virtual std::pair<Color, std::vector<Ray>> intersect(Ray ray) const = 0;
};

#endif
