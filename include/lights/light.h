#ifndef LIGHT_H
#define LIGHT_H

#include "color.h"
#include "defs.h"
#include "vector3f.h"

class Scene;

// Base class for all light sources
class Light {
  // The scene which contains this light
  Scene *scene = nullptr;
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

  Scene *getScene() const noexcept { return scene; }
  void setScene(Scene *scene) noexcept { this->scene = scene; }
};

#endif /* end of include guard: LIGHT_H */
