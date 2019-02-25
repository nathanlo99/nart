
#include "objects/model.h"

#include "color.h"
#include "defs.h"
#include "ray.h"

#include <array>
#include <climits>
#include <fstream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

Model::Model(const std::string &name, ModelTraits option) {
  INFO("Loading model " + name);
  const std::string obj_file_name =
      (option == ModelTraits::MODEL)
          ? ("res/models/" + name + "/" + name + ".obj")
          : ("res/objs/" + name + ".obj");
  INFO("Object file at " + obj_file_name);

  if (option == ModelTraits::MODEL) {
    // Load .mtl file here
  }

  // Load .obj file here
  std::ifstream obj_file(obj_file_name);
  if (!obj_file)
    ERROR("Could not open obj file: " + obj_file_name);

  std::vector<Vector3f> vertices;
  std::vector<TextureCoord> texture_coords;
  std::vector<Vector3f> normals;

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
  INFO("Loaded " + name + ": " + std::to_string(data.size()) + " faces, " +
       std::to_string(vertices.size() - 1) + " vertices, " +
       std::to_string(texture_coords.size() - 1) + " texture coords, " +
       std::to_string(normals.size() - 1) + " normals");
}

bool Face::intersects(const Ray &ray, double max_dist) const {
  const double vn = ray.direction.dot(plane_normal);
  if (fzero(vn))
    return false;
  const double dist = (vertex_a - ray.start).dot(plane_normal) / vn;
  if (dist > max_dist || dist < accuracy)
    return false;
  const Vector3f point = ray.start + dist * ray.direction;
  const double cross1 =
      (vertex_c - vertex_a).cross(point - vertex_a).dot(plane_normal);
  if (cross1 > 0)
    return false;
  const double cross2 =
      (vertex_a - vertex_b).cross(point - vertex_b).dot(plane_normal);
  if (cross2 > 0)
    return false;
  const double cross3 =
      (vertex_b - vertex_c).cross(point - vertex_c).dot(plane_normal);
  if (cross3 > 0)
    return false;
  return true;
}

std::tuple<double, Color, Vector3f> Face::intersect(const Ray &ray,
                                                    double max_dist) const {
  const double vn = ray.direction.dot(plane_normal);
  if (fzero(vn))
    return {-1, {0, 0, 0}, {0, 0, 0}};
  const double dist = (vertex_a - ray.start).dot(plane_normal) / vn;
  if (dist > max_dist || dist < 0)
    return {-1, {0, 0, 0}, {0, 0, 0}};
  const Vector3f point = ray.start + dist * ray.direction;
  const double cross1 =
      (vertex_c - vertex_a).cross(point - vertex_a).dot(plane_normal);
  if (cross1 > 0)
    return {-1, {0, 0, 0}, {0, 0, 0}};
  const double cross2 =
      (vertex_a - vertex_b).cross(point - vertex_b).dot(plane_normal);
  if (cross2 > 0)
    return {-1, {0, 0, 0}, {0, 0, 0}};
  const double cross3 =
      (vertex_b - vertex_c).cross(point - vertex_c).dot(plane_normal);
  if (cross3 > 0)
    return {-1, {0, 0, 0}, {0, 0, 0}};
  return {dist, Color::WHITE, plane_normal};
}

bool Model::intersects(const Ray &ray, double max_dist) const {
  for (const auto &face : data) {
    if (face.intersects(ray, max_dist))
      return true;
  }
  return false;
}

std::tuple<double, Color, Vector3f> Model::intersect(const Ray &ray,
                                                     double max_dist) const {
  double min_dist = 10000.0, cur_dist;
  bool intersected = false;
  Color min_color = Color::BLACK, cur_color;
  Vector3f min_normal{0, 0, 0}, cur_normal{0, 0, 0};

  for (const auto &face : data) {
    const auto &intersect_result = face.intersect(ray, min_dist);
    std::tie(cur_dist, cur_color, cur_normal) = intersect_result;
    if (cur_dist > accuracy && cur_dist < min_dist) {
      std::tie(min_dist, min_color, min_normal) = intersect_result;
      intersected = true;
    }
  }

  if (intersected)
    return {min_dist, min_color, min_normal};
  else
    return {-1, {0, 0, 0}, {0, 0, 0}};
}
