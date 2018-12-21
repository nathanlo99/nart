#ifndef CAMERA_H
#define CAMERA_H

#include "vector3f.h"

class Camera final {
  Vector3f location, look_at;

public:
  Camera(Vector3f location, Vector3f look_at)
      : location{location}, look_at{look_at} {}
  ~Camera() {}
};

#endif /* end of include guard: CAMERA_H */
