
#pragma once

#include "common.h"
#include "light.h"

// A simple light which radiates the same colour in every direction
class PointLight : public Light {
  // The colour of the light
  vec3 colour;

public:
  PointLight(const vec3 &loc, const vec3 &colour)
      : Light{loc}, colour(colour) {}
  vec3 get_colour(const vec3 &from) const override { return colour; }
};
