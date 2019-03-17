
#ifndef UTIL_H
#define UTIL_H

#include "objects/model.h"
#include "ray.h"
#include <vector>

std::vector<Face> loadOBJ(const std::string &obj_file_name);

bool intersectsAABB(Ray ray, Vector3f p1, Vector3f p2) noexcept;

#endif /* end of include guard: UTIL_H */
