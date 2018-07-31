#ifndef MESH_H
#define MESH_H

#include <string>

#include "Object.h"

class Mesh : public Object {
private:
  /* data */

public:
  Mesh(std::string fileName);
  Mesh(const Mesh &other);
  virtual ~Mesh();
};

#endif
