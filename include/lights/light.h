#ifndef LIGHT_H
#define LIGHT_H

#include "color.h"
#include "defs.h"
#include "vector3f.h"

class World;

// Base class for all light sources
class Light {
  // The world which contains this light
  World *world = nullptr;
  // The position of the light in space
  Vector3f pos;

public:
  explicit Light(const Vector3f &pos) : pos{pos} {}
  virtual ~Light() {}

  // Returns the position of a light, useful to cast a ray towards for shadows
  Vector3f getPos() const noexcept { return pos; }
  // Returns the color of the light headed in the direction of 'from', can be
  // overloaded for directional lights, multi-colored lights, etc.
  virtual Color getColor(const Vector3f &from) const = 0;

  World *getWorld() const noexcept { return world; }
  void setWorld(World *world) noexcept { this->world = world; }
};

#endif /* end of include guard: LIGHT_H */
