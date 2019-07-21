#ifndef CAMERA_H
#define CAMERA_H

#include "defs.h"

#include "vector3f.h"

// Encapsulates data about the point from which rays are cast
class Camera final {
  // The location of the camera, as well as normalized vectors for the three
  // relative directions
  Vector3f location, forward, right, up;
  // Screen width and height in pixels
  size_t screen_width = 320, screen_height = 200;
  // Horizontal field of view, in degrees
  double horizontal_fov = 60;

public:
  Camera(const Vector3f &location, const Vector3f &look_at,
         const Vector3f &upward = Vector3f{0, 0, 1}) noexcept
      : location{location}, forward{(look_at - location).normalize()},
        right{forward.cross(upward).normalize()},
        up{right.cross(forward).normalize()} {}

  Camera(const Vector3f &location, const Vector3f &look_at,
         const Vector3f &upward = Vector3f{0, 0, 1}, size_t screen_width,
         size_t screen_height, float horizontal_fov) noexcept
      : location{location}, forward{(look_at - location).normalize()},
        right{forward.cross(upward).normalize()},
        up{right.cross(forward).normalize()}, screen_width{screen_width},
        screen_height{screen_height}, horizontal_fov{horizontal_fov} {}

  const Vector3f &getP() const noexcept { return location; }
  const Vector3f &getF() const noexcept { return forward; }
  const Vector3f &getR() const noexcept { return right; }
  const Vector3f &getU() const noexcept { return up; }
  const size_t getWidth() const noexcept { return screen_width; }
  const size_t getHeight() const noexcept { return screen_height; }
  const size_t getFOV() const noexcept { return horizontal_fov; }
};

#endif /* end of include guard: CAMERA_H */
