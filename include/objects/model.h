#ifndef MODEL_H
#define MODEL_H

#include <string>
#include <tuple>
#include <vector>

#include "color.h"
#include "defs.h"
#include "image.h"
#include "material.h"
#include "objects/object.h"
#include "ray.h"
#include "vector3f.h"

enum ModelTraits { OBJ, MODEL };

struct TextureCoord {
  float x = 0, y = 0;
  TextureCoord() {}
  TextureCoord(float x, float y) : x{x}, y{y} {}
};

struct Face : public Object {
  Vector3f vertex_a, vertex_b, vertex_c;
  Vector3f plane_normal, normal_a, normal_b, normal_c;
  TextureCoord texture_a, texture_b, texture_c;
  Material material;

  Face(const Vector3f &a, const Vector3f &b, const Vector3f &c)
      : vertex_a{a}, vertex_b{b}, vertex_c{c},
        plane_normal{(c - b).cross(a - b).normalize()}, normal_a{plane_normal},
        normal_b{plane_normal}, normal_c{plane_normal}, material{} {}

  Face(const Vector3f &a, const Vector3f &b, const Vector3f &c,
       TextureCoord texture_a, TextureCoord texture_b, TextureCoord texture_c,
       const Vector3f &normal_a, const Vector3f &normal_b,
       const Vector3f &normal_c)
      : vertex_a{a}, vertex_b{b}, vertex_c{c},
        plane_normal{(c - b).cross(a - b).normalize()}, normal_a{normal_a},
        normal_b{normal_b}, normal_c{normal_c}, texture_a{texture_a},
        texture_b{texture_b}, texture_c{texture_c} {
    if (fzero(normal_a.norm()))
      this->normal_a = this->normal_b = this->normal_c = plane_normal;
  }

  std::tuple<double, Color, Vector3f> intersect(const Ray &ray) const override;
};

class Model : public Object {
  std::vector<Face> data;

public:
  explicit Model(const std::string &name, ModelTraits option = MODEL);
  ~Model() {}

  std::tuple<double, Color, Vector3f> intersect(const Ray &ray) const override;
};

#endif
