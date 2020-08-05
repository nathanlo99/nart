
#pragma once

#include "defs.h"

// Encapsulates data about the point from which rays are cast
class Camera final {
  // The location of the camera, as well as normalized vectors for the three
  // relative directions
  vec3 location, forward, right, up;

public:
  Camera(const vec3 &location, const vec3 &look_at,
         const vec3 &upward = vec3{0.0f, 0.0f, 1.0f}) noexcept
      : location{location}, forward{(look_at - location).normalize()},
        right{forward.cross(upward).normalize()},
        up{right.cross(forward).normalize()} {}

  const vec3 &getP() const noexcept { return location; }
  const vec3 &getF() const noexcept { return forward; }
  const vec3 &getR() const noexcept { return right; }
  const vec3 &getU() const noexcept { return up; }
};
