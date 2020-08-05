
#pragma once

#include "common.h"

class Scene;

// Base class for all light sources
class Light {
  // The scene which contains this light
  Scene *scene = nullptr;
  // The position of the light in space
  vec3 pos;

public:
  explicit Light(const vec3 &pos) : pos(pos) {}
  virtual ~Light() {}

  // Returns the position of a light, useful to cast a ray towards for shadows
  vec3 get_position() const noexcept { return pos; }
  // Returns the colour of the light headed in the direction of 'from', can be
  // overloaded for directional lights, multi-coloured lights, etc.
  virtual vec3 get_colour(const vec3 &from) const = 0;

  Scene *get_scene() const noexcept { return scene; }
  void set_scene(Scene *scene) noexcept { this->scene = scene; }
};
