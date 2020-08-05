#ifndef CAMERA_H
#define CAMERA_H

#include "common.h"

// Encapsulates data about the point from which rays are cast
class Camera final {
  // The location of the camera, as well as normalized vectors for the three
  // relative directions
  vec3 location, forward, right, up;

public:
  Camera(const vec3 &location, const vec3 &look_at,
         const vec3 &upward = vec3{0, 0, 1}) noexcept
      : location{location}, forward{glm::normalize(look_at - location)},
        right{glm::normalize(glm::cross(forward, upward))},
        up{glm::normalize(glm::cross(right, forward))} {}

  const vec3 &getP() const noexcept { return location; }
  const vec3 &getF() const noexcept { return forward; }
  const vec3 &getR() const noexcept { return right; }
  const vec3 &getU() const noexcept { return up; }
};

#endif /* end of include guard: CAMERA_H */
