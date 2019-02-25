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

  virtual bool intersects(const Ray &ray, double max_dist) const = 0;

  virtual std::tuple<double, Color, Vector3f>
  intersect(const Ray &ray, double max_dist) const = 0;

  World *getWorld() { return world; }
  void setWorld(World *world) { this->world = world; }
};

#endif
