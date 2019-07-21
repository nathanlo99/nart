#ifndef MATERIAL_H
#define MATERIAL_H

#include "color.h"
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
  Color ambient = Color::WHITE, diffuse = Color::WHITE, spectral = Color::WHITE;
  float transparency = 0.f;
  int illum = 0;
  std::shared_ptr<Image> ambient_texture, diffuse_texture;
};

#endif /* end of include guard: MATERIAL_H */
