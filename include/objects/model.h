#ifndef MODEL_H
#define MODEL_H

#include <string>
#include <vector>

#include "color.h"
#include "image.h"
#include "objects/object.h"
#include "ray.h"
#include "vector3f.h"

enum ModelTraits { OBJ, MODEL };

// Helpful resource:
// https://people.cs.clemson.edu/~dhouse/courses/405/docs/brief-mtl-file-format.html
//   Provides .mtl file format reference as well as formulas to be used later

struct Material {
  std::string name;
  Color ambient, diffuse, spectral;
  float transparency;
  int illum;
  std::unique_ptr<Image> ambient_texture, diffuse_texture;
};

struct TextureCoord {
  float x, y;
};

struct Face {
  Vector3f vertex_a, vertex_b, vertex_c;
  Vector3f normal_a, normal_b, normal_c;
  TextureCoord texture_a, texture_b, texture_c;
  Material material;
};

class Model : public Object {
  std::vector<Face> data;

public:
  explicit Model(const std::string &file_name, ModelTraits option = MODEL);
  ~Model() {}

  Color intersect(const Ray &ray) const override;
};

#endif
