
#pragma once

#include "objects/model.h"
#include "ray.h"
#include <vector>

// Loads a .obj file and returns a list of triangles
RawOBJ loadOBJ(const std::string &obj_file_name);

// Returns true if the specified ray intersects the axis-aligned bounding box
// specified by opposite corners 'p1' and 'p2'
bool intersectsAABB(const Ray &ray, const vec3 &p1, const vec3 &p2,
                    const float min_dist = 0.0f,
                    const float max_dist = inf) noexcept;
