#ifndef MODEL_H
#define MODEL_H

#include <string>
#include <tuple>
#include <vector>

#include "color.h"
#include "common.h"
#include "image.h"
#include "material.h"
#include "objects/object.h"
#include "ray.h"

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
  vec3 vertex_a, vertex_b, vertex_c;
  // 'plane_normal' is the normal of the triangle, the others are the normals
  // from the model, used to interpolate and smooth
  vec3 plane_normal, normal_a, normal_b, normal_c;
  // Textures from the model directory, used for interpolation
  TextureCoord texture_a, texture_b, texture_c;
  // Stores reflective/refractive properties of the object
  Material material;

  Face(const vec3 &a, const vec3 &b, const vec3 &c) noexcept
      : vertex_a{a}, vertex_b{b}, vertex_c{c}, plane_normal{glm::normalize(
                                                   glm::cross(b - a, c - a))},
        normal_a{plane_normal}, normal_b{plane_normal}, normal_c{plane_normal},
        material{} {}

  Face(const vec3 &a, const vec3 &b, const vec3 &c, TextureCoord texture_a,
       TextureCoord texture_b, TextureCoord texture_c, const vec3 &normal_a,
       const vec3 &normal_b, const vec3 &normal_c) noexcept
      : vertex_a{a}, vertex_b{b}, vertex_c{c}, plane_normal{glm::normalize(
                                                   glm::cross(b - a, c - a))},
        normal_a{normal_a}, normal_b{normal_b}, normal_c{normal_c},
        texture_a{texture_a}, texture_b{texture_b}, texture_c{texture_c} {
    if (fzero(glm::length(normal_a)))
      this->normal_a = this->normal_b = this->normal_c = plane_normal;
  }

  bool intersects(const Ray &ray, float min_dist,
                  float max_dist) const override;
  std::tuple<float, Color, vec3> intersect(const Ray &ray,
                                           float max_dist) const override;
};

struct RawOBJ {
  std::vector<vec3> vertices;
  std::vector<std::tuple<int, int, int>> triangles;
  std::vector<Face> data;

  RawOBJ() : vertices{}, triangles{}, data{} {}
  RawOBJ(std::vector<vec3> vertices,
         std::vector<std::tuple<int, int, int>> triangles,
         std::vector<Face> data)
      : vertices{vertices}, triangles{triangles}, data{data} {}
};

// A 3D model, possibly textured
class Model : public Object {
  RawOBJ rawOBJ;
  std::vector<Face> data;
  vec3 min_corner, max_corner;

public:
  explicit Model(const std::string &name, ModelTraits option = MODEL);
  ~Model() noexcept {}

  bool intersects(const Ray &ray, float min_dist,
                  float max_dist) const override;
  std::tuple<float, Color, vec3> intersect(const Ray &ray,
                                           float max_dist) const override;
};

#endif
