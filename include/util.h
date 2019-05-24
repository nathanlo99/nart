
#ifndef UTIL_H
#define UTIL_H

#include "objects/model.h"
#include "ray.h"
#include <vector>

// Loads a .obj file and returns a list of triangles
RawOBJ loadOBJ(const std::string &obj_file_name);

// Returns true if the specified ray intersects the axis-aligned bounding box
// specified by opposite corners 'p1' and 'p2'
bool intersectsAABB(const Ray &ray, const Vector3f &p1, const Vector3f &p2,
                    const double min_dist = accuracy,
                    const double max_dist = 10000.0) noexcept;

#endif /* end of include guard: UTIL_H */
