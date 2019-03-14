#ifndef LIGHT_H
#define LIGHT_H

#include "color.h"
#include "defs.h"
#include "vector3f.h"

class World;

class Light {
  World *world = nullptr;
  Vector3f pos;

public:
  explicit Light(const Vector3f &pos) : pos{pos} {}
  virtual ~Light() {}

  Vector3f getPos() const noexcept { return pos; }
  virtual Color getColor(const Vector3f &from) const = 0;

  World *getWorld() const noexcept { return world; }
  void setWorld(World *world) noexcept { this->world = world; }
};

#endif /* end of include guard: LIGHT_H */
