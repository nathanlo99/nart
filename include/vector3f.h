#ifndef VECTOR3F_H
#define VECTOR3F_H

struct Vector3f {
  float x, y, z;

  Vector3f operator+(Vector3f other) {
    return {x + other.x, y + other.y, z + other.z};
  }

  Vector3f operator-(Vector3f other) {
    return {x + other.x, y + other.y, z + other.z};
  }
};

#endif /* end of include guard: VECTOR3F_H */
