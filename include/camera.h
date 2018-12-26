#ifndef CAMERA_H
#define CAMERA_H

#include "defs.h"

#include "vector3f.h"

class Camera final {
  Vector3f location, forward, right, up;

public:
  Camera(Vector3f location, Vector3f look_at,
         Vector3f upward = (Vector3f){0, 0, 1})
      : location{location}, forward{look_at.normalize()},
        right{forward.cross(upward).normalize()},
        up{right.cross(forward).normalize()} {}

  const Vector3f &getP() const { return location; }
  const Vector3f &getF() const { return forward; }
  const Vector3f &getR() const { return right; }
  const Vector3f &getU() const { return up; }
};

#endif /* end of include guard: CAMERA_H */
