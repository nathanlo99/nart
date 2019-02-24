#ifndef POINT_LIGHT
#define POINT_LIGHT

#include "color.h"
#include "defs.h"
#include "light.h"
#include "vector3f.h"

class PointLight : public Light {
  Color color;

public:
  PointLight(const Vector3f &loc, const Color &color)
      : Light{loc}, color{color} {}
  Color getColor(const Vector3f &from) const override { return color; }
};

#endif /* end of include guard: POINT_LIGHT */
