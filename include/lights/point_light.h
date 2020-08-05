
#pragma once

#include "defs.h"
#include "light.h"
#include "vector3.h"

// A simple light which radiates the same color in every direction
class PointLight : public Light {
  // The color of the light
  vec3 color;

public:
  PointLight(const vec3 &loc, const vec3 &color) : Light{loc}, color{color} {}
  vec3 getvec3(const vec3 &from) const override { return color; }
};
