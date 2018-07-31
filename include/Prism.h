#ifndef SPHERE_H
#define SPHERE_H

#include "Object.h"

class Sphere : public Object {
private:
  /* data */

public:
  Sphere();
  Sphere(const Sphere &other);
  virtual ~Sphere();
};

#endif
