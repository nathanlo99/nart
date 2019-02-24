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
  std::string name = "default";
  Color ambient = Color::WHITE, diffuse = Color::WHITE, spectral = Color::WHITE;
  float transparency = 0.f;
  int illum = 0;
  std::unique_ptr<Image> ambient_texture, diffuse_texture;
};

struct TextureCoord {
  float x = 0, y = 0;
  TextureCoord() {}
  TextureCoord(float x, float y) : x{x}, y{y} {}
};

struct Face {
  Vector3f vertex_a, vertex_b, vertex_c;
  Vector3f normal_a, normal_b, normal_c;
  TextureCoord texture_a, texture_b, texture_c;
  Material material;

  Face(Vector3f a, Vector3f b, Vector3f c)
      : vertex_a{a}, vertex_b{b}, vertex_c{c},
        normal_a{(c - b).cross(a - b).normalize()}, normal_b{normal_a},
        normal_c{normal_a}, material{} {}
  Face(Vector3f a, Vector3f b, Vector3f c, TextureCoord texture_a,
       TextureCoord texture_b, TextureCoord texture_c, Vector3f normal_a,
       Vector3f normal_b, Vector3f normal_c)
      : vertex_a{a}, vertex_b{b}, vertex_c{c}, normal_a{normal_a},
        normal_b{normal_b}, normal_c{normal_c}, texture_a{texture_a},
        texture_b{texture_b}, texture_c{texture_c} {}
};

class Model : public Object {
  std::vector<Face> data;

public:
  explicit Model(const std::string &name, ModelTraits option = MODEL);
  ~Model() {}

  std::pair<double, Color> intersect(const Ray &ray) const override;
};

#endif
