#ifndef CAMERA_H
#define CAMERA_H

#include "defs.h"

#include "vector3f.h"

class Camera final {
  Vector3f location, forward, right, up;

public:
  Camera(const Vector3f &location, const Vector3f &look_at,
         const Vector3f &upward = Vector3f{0, 0, 1}) noexcept
      : location{location}, forward{(look_at - location).normalize()},
        right{forward.cross(upward).normalize()},
        up{right.cross(forward).normalize()} {}

  const Vector3f &getP() const noexcept { return location; }
  const Vector3f &getF() const noexcept { return forward; }
  const Vector3f &getR() const noexcept { return right; }
  const Vector3f &getU() const noexcept { return up; }
};

#endif /* end of include guard: CAMERA_H */
