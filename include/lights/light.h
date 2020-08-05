
#include "color.h"
#include "common.h"

class Scene;

// Base class for all light sources
class Light {
  // The scene which contains this light
  Scene *scene = nullptr;
  // The position of the light in space
  vec3 pos;

public:
  explicit Light(const vec3 &pos) : pos{pos} {}
  virtual ~Light() {}

  // Returns the position of a light, useful to cast a ray towards for shadows
  vec3 getPos() const noexcept { return pos; }
  // Returns the color of the light headed in the direction of 'from', can be
  // overloaded for directional lights, multi-colored lights, etc.
  virtual Color getColor(const vec3 &from) const = 0;

  Scene *getScene() const noexcept { return scene; }
  void setScene(Scene *scene) noexcept { this->scene = scene; }
};
