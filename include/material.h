
#pragma once

#include "defs.h"
#include "image.h"

#include <string>
#include <utility>

// NOTE: Helpful resource:
// https://people.cs.clemson.edu/~dhouse/courses/405/docs/brief-mtl-file-format.html
//   Provides .mtl file format reference as well as formulas to be used later

// Encapsulates the spectral properties of a material used in Phong shading,
// currently only used in Model, but can be used to extend existing primitives
struct Material {
  std::string name = "default_material";
  vec3 ambient = vec3(1, 1, 1), diffuse = vec3(1, 1, 1),
       spectral = vec3(1, 1, 1);
  float transparency = 0;
  int illum = 0;
  std::shared_ptr<Image> ambient_texture, diffuse_texture;
};
