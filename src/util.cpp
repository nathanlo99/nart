
#include "util.h"

#include "defs.h"
#include "image.h"
#include "objects/model.h"
#include <fstream>
#include <sstream>
#include <vector>

RawOBJ loadOBJ(const std::string &obj_file_name) {
  std::ifstream obj_file(obj_file_name);
  if (!obj_file)
    ERROR("Could not open obj file: " + obj_file_name);

  std::vector<vec3> vertices;
  std::vector<std::tuple<int, int, int>> triangles;
  std::vector<TextureCoord> texture_coords;
  std::vector<vec3> normals;
  std::vector<Face> data;

  vertices.emplace_back(0, 0, 0);
  texture_coords.emplace_back(-1, -1);
  normals.emplace_back(0, 0, 0);

  std::string cur_line;
  while (std::getline(obj_file, cur_line)) {
    if (cur_line == "")
      continue;
    std::stringstream cur_line_stream(cur_line);
    std::string line_kind;
    std::getline(cur_line_stream, line_kind, ' ');
    if (line_kind == "#") { // Comment line
      continue;
    } else if (line_kind == "v") { // Vertex
      float x = 0, y = 0, z = 0;
      cur_line_stream >> x >> z >> y;
      vertices.emplace_back(x, y, z);
    } else if (line_kind == "vt") { // Texture coordinates
      float u = 0, v = 0;
      cur_line_stream >> u >> v;
      texture_coords.emplace_back(u, v);
    } else if (line_kind == "vn") { // Normals
      float x = 0, y = 0, z = 0;
      cur_line_stream >> x >> y >> z;
      normals.emplace_back(x, y, z);
    } else if (line_kind == "f") { // Face
      std::string token;
      std::vector<std::tuple<unsigned int, unsigned int, unsigned int>> indices;
      while (std::getline(cur_line_stream, token, ' ')) {
        std::stringstream token_stream{token};
        std::array<int, 3> cur_indices{0, 0, 0};

        std::string sub_token;
        unsigned int sub_token_num = 0;
        while (std::getline(token_stream, sub_token, '/')) {
          const int index = sub_token == "" ? 0 : std::atoi(sub_token.c_str());
          cur_indices[sub_token_num] = index;
          sub_token_num++;
        }

        indices.emplace_back(cur_indices[0], cur_indices[1], cur_indices[2]);
      }

      if (indices.size() != 3)
        ERROR("Faces with != 3 vertices not yet supported");

      const auto &[v1, vt1, vn1] = indices[0];
      const auto &[v2, vt2, vn2] = indices[1];
      const auto &[v3, vt3, vn3] = indices[2];
      const vec3 vertex_a = vertices[v1], vertex_b = vertices[v2],
                 vertex_c = vertices[v3];
      const TextureCoord texture_a = texture_coords[vt1],
                         texture_b = texture_coords[vt2],
                         texture_c = texture_coords[vt3];
      const vec3 normal_a = normals[vn1], normal_b = normals[vn2],
                 normal_c = normals[vn3];
      triangles.emplace_back(v1, v2, v3);
      data.emplace_back(vertex_a, vertex_b, vertex_c, texture_a, texture_b,
                        texture_c, normal_a, normal_b, normal_c);
    } else if (line_kind == "usemtl") {

    } else if (line_kind == "mtllib") {

    } else if (line_kind == "s") {

    } else if (line_kind == "g") {

    } else {
      INFO("Unknown .obj characteristic: " + line_kind + " in line '" +
           cur_line + "'");
    }
  }
  INFO("Loaded " + obj_file_name + ": " + std::to_string(data.size()) +
       " faces, " + std::to_string(vertices.size() - 1) + " vertices, " +
       std::to_string(texture_coords.size() - 1) + " texture coords, " +
       std::to_string(normals.size() - 1) + " normals");
  return {vertices, triangles, data};
}

constexpr inline std::pair<float, float> getInterval(const float start,
                                                     const float direction,
                                                     const float min,
                                                     const float max) {
  if (fzero(direction)) {
    if (min <= start && start <= max) {
      const float inf = std::numeric_limits<float>::infinity();
      return std::make_pair(-inf, inf);
    } else
      return std::make_pair(0, 0);
  } else if (direction > 0) {
    return std::make_pair((min - start) / direction, (max - start) / direction);
  } else {
    return std::make_pair((max - start) / direction, (min - start) / direction);
  }
}

bool intersectsAABB(const Ray &ray, const vec3 &p1, const vec3 &p2,
                    const float min_dist, const float max_dist) noexcept {
  float interval_min = std::max(0.0f, min_dist), interval_max = max_dist;
  const auto &[x_min, x_max] =
      getInterval(ray.start.x, ray.direction.x, p1.x, p2.x);
  interval_min = std::max(interval_min, x_min);
  interval_max = std::min(interval_max, x_max);
  if (interval_min >= interval_max)
    return false;
  const auto &[y_min, y_max] =
      getInterval(ray.start.y, ray.direction.y, p1.y, p2.y);
  interval_min = std::max(interval_min, y_min);
  interval_max = std::min(interval_max, y_max);
  if (interval_min >= interval_max)
    return false;
  const auto &[z_min, z_max] =
      getInterval(ray.start.z, ray.direction.z, p1.z, p2.z);
  interval_min = std::max(interval_min, z_min);
  interval_max = std::min(interval_max, z_max);
  return interval_min < interval_max;
}
