
#include "util.h"

#include "defs.h"
#include "image.h"
#include "objects/model.h"
#include <fstream>
#include <sstream>
#include <vector>

std::vector<Face> loadOBJ(const std::string &obj_file_name) {
  std::ifstream obj_file(obj_file_name);
  if (!obj_file)
    ERROR("Could not open obj file: " + obj_file_name);

  std::vector<Vector3f> vertices;
  std::vector<TextureCoord> texture_coords;
  std::vector<Vector3f> normals;
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
      double x = 0, y = 0, z = 0;
      cur_line_stream >> x >> z >> y;
      vertices.emplace_back(x, y, z);
    } else if (line_kind == "vt") { // Texture coordinates
      float u = 0, v = 0;
      cur_line_stream >> u >> v;
      texture_coords.emplace_back(u, v);
    } else if (line_kind == "vn") { // Normals
      double x = 0, y = 0, z = 0;
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
      // std::cout << cur_line << std::endl;
      // std::cout << indices << std::endl;
      if (indices.size() != 3)
        ERROR("Faces with != 3 vertices not yet supported");

      unsigned int v1, v2, v3, vt1, vt2, vt3, vn1, vn2, vn3;
      std::tie(v1, vt1, vn1) = indices[0];
      std::tie(v2, vt2, vn2) = indices[1];
      std::tie(v3, vt3, vn3) = indices[2];
      const Vector3f vertex_a = vertices[v1], vertex_b = vertices[v2],
                     vertex_c = vertices[v3];
      const TextureCoord texture_a = texture_coords[vt1],
                         texture_b = texture_coords[vt2],
                         texture_c = texture_coords[vt3];
      const Vector3f normal_a = normals[vn1], normal_b = normals[vn2],
                     normal_c = normals[vn3];
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
  return data;
}

bool intersectsAABB(Ray ray, Vector3f p1, Vector3f p2) noexcept {
  //
}
