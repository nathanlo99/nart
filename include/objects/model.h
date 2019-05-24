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

// Used as an argument to the Model constructor, differentiates between .obj
// (standalone 3D models) and models (.obj's with textures)
enum ModelTraits { OBJ, MODEL };

// A texture coordinate in a texture file, stored in pixels. They are
// floating-point numbers to support exact interpolation on triangular meshes
struct TextureCoord {
  float x = 0, y = 0;
  TextureCoord() noexcept {}
  TextureCoord(float x, float y) noexcept : x{x}, y{y} {}
};

// A face stores all the necessary information stored in an individual triangle
// of a model
struct Face : public Object {
  // The positions of the three vertices *stored counter-clockwise if looking
  // from 'outside'*
  Vector3f vertex_a, vertex_b, vertex_c;
  // 'plane_normal' is the normal of the triangle, the others are the normals
  // from the model, used to interpolate and smooth
  Vector3f plane_normal, normal_a, normal_b, normal_c;
  // Textures from the model directory, used for interpolation
  TextureCoord texture_a, texture_b, texture_c;
  // Stores reflective/refractive properties of the object
  Material material;

  Face(const Vector3f &a, const Vector3f &b, const Vector3f &c) noexcept
      : vertex_a{a}, vertex_b{b}, vertex_c{c},
        plane_normal{(b - a).cross(c - a).normalize()}, normal_a{plane_normal},
        normal_b{plane_normal}, normal_c{plane_normal}, material{} {}

  Face(const Vector3f &a, const Vector3f &b, const Vector3f &c,
       TextureCoord texture_a, TextureCoord texture_b, TextureCoord texture_c,
       const Vector3f &normal_a, const Vector3f &normal_b,
       const Vector3f &normal_c) noexcept
      : vertex_a{a}, vertex_b{b}, vertex_c{c},
        plane_normal{(b - a).cross(c - a).normalize()}, normal_a{normal_a},
        normal_b{normal_b}, normal_c{normal_c}, texture_a{texture_a},
        texture_b{texture_b}, texture_c{texture_c} {
    if (fzero(normal_a.norm()))
      this->normal_a = this->normal_b = this->normal_c = plane_normal;
  }

  bool intersects(const Ray &ray, double min_dist,
                  double max_dist) const override;
  std::tuple<double, Color, Vector3f> intersect(const Ray &ray,
                                                double max_dist) const override;
};

struct RawOBJ {
  std::vector<Vector3f> vertices;
  std::vector<std::tuple<int, int, int>> triangles;
  std::vector<Face> data;

  RawOBJ() : vertices{}, triangles{}, data{} {}
  RawOBJ(std::vector<Vector3f> vertices,
         std::vector<std::tuple<int, int, int>> triangles,
         std::vector<Face> data)
      : vertices{vertices}, triangles{triangles}, data{data} {}
};

// A 3D model, possibly textured
class Model : public Object {
  RawOBJ rawOBJ;
  std::vector<Face> data;
  Vector3f min_corner, max_corner;

public:
  explicit Model(const std::string &name, ModelTraits option = MODEL);
  ~Model() noexcept {}

  bool intersects(const Ray &ray, double min_dist,
                  double max_dist) const override;
  std::tuple<double, Color, Vector3f> intersect(const Ray &ray,
                                                double max_dist) const override;
};

#endif
