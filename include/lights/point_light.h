#ifndef POINT_LIGHT
#define POINT_LIGHT

#include "color.h"
#include "common.h"
#include "light.h"

// A simple light which radiates the same color in every direction
class PointLight : public Light {
  // The color of the light
  Color color;

public:
  PointLight(const vec3 &loc, const Color &color) : Light{loc}, color{color} {}
  Color getColor(const vec3 &from) const override { return color; }
};

#endif /* end of include guard: POINT_LIGHT */
