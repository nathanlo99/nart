#ifndef RAY_H
#define RAY_H

#include "vector3f.h"

class Ray {
  Vector3f start, direction;

public:
  Ray(Vector3f start, Vector3f direction)
      : start{start}, direction{direction} {}
};

#endif /* end of include guard: RAY_H */
