#ifndef OBJECT_H
#define OBJECT_H

#include "color.h"
#include "ray.h"

#include <utility>
#include <vector>

class World;

// A base class for all objects with which light can interact.
class Object {

protected:
  // The world which contains this object
  World *world = nullptr;

public:
  Object() {}
  virtual ~Object() noexcept {}

  // Returns true if the specified ray intersects the object, and the distance
  // from the ray's starting position and the intersection point is between
  // min_dist and max_dist, inclusive (up to accuracy of the floating point
  // used)
  virtual bool intersects(const Ray &ray, double min_dist,
                          double max_dist) const = 0;

  // If the ray intersects within max_dist of the ray's starting position,
  // returns a pair containing the distance, the color, and the (normalized)
  // normal vector. Otherwise, returns any tuple with a negative distance.
  virtual std::tuple<double, Color, Vector3f>
  intersect(const Ray &ray, double max_dist) const = 0;

  World *getWorld() const noexcept { return world; }
  void setWorld(World *world) noexcept { this->world = world; }
};

#endif
