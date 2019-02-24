#ifndef MATERIAL_H
#define MATERIAL_H

#include "defs.h"
#include "color.h"
#include "image.h"

#include <string>
#include <utility>

// Helpful resource:
// https://people.cs.clemson.edu/~dhouse/courses/405/docs/brief-mtl-file-format.html
//   Provides .mtl file format reference as well as formulas to be used later
struct Material {
  std::string name = "default";
  Color ambient = Color::WHITE, diffuse = Color::WHITE, spectral = Color::WHITE;
  float transparency = 0.f;
  int illum = 0;
  std::unique_ptr<Image> ambient_texture, diffuse_texture;
};

#endif /* end of include guard: MATERIAL_H */
