#ifndef OBJECT_H
#define OBJECT_H

#include "color.h"
#include "ray.h"

#include <utility>
#include <vector>

class World;

class Object {

protected:
  World *world = nullptr;

public:
  Object() {}
  virtual ~Object() {}

  virtual std::pair<double, Color> intersect(const Ray &ray) const = 0;

  World *getWorld() { return world; }
  void setWorld(World *world) { this->world = world; }
};

#endif
