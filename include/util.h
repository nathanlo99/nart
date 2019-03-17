
#ifndef UTIL_H
#define UTIL_H

#include "objects/model.h"
#include "ray.h"
#include <vector>

// Loads a .obj file and returns a list of triangles
std::vector<Face> loadOBJ(const std::string &obj_file_name);

// Returns true if the specified ray intersects the axis-aligned bounding box
// specified by opposite corners 'p1' and 'p2'
bool intersectsAABB(Ray ray, Vector3f p1, Vector3f p2,
                    double min_dist = accuracy,
                    double max_dist = 10000.0) noexcept;

#endif /* end of include guard: UTIL_H */
