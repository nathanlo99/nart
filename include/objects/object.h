#ifndef OBJECT_H
#define OBJECT_H

#include "color.h"
#include "ray.h"

#include <utility>
#include <vector>

class World;

class Object {

public:
  Object() {}
  virtual ~Object() {}

  virtual std::pair<Color, std::vector<Ray>>
  intersect(const Ray &ray) const = 0;
};

#endif
