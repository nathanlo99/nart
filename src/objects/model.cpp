
#include "objects/model.h"

#include "common.h"
#include "ray.h"
#include "util.h"

#include <array>
#include <cassert>
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
  rawOBJ = loadOBJ(obj_file_name);
  data = rawOBJ.data;

  assert(!rawOBJ.vertices.empty());

  min_corner = max_corner = rawOBJ.vertices[0];
  for (const auto &vertex : rawOBJ.vertices) {
    min_corner = min(min_corner, vertex);
    max_corner = max(max_corner, vertex);
  }

  // std::cout << min_corner << ", " << max_corner << std::endl;
}

bool Face::intersects(const Ray &ray, float min_dist, float max_dist) const {
  const float vn = glm::dot(ray.direction, plane_normal);
  if (fzero(vn))
    return false;
  const float dist = glm::dot(vertex_a - ray.start, plane_normal) / vn;
  if (dist < min_dist || dist > max_dist)
    return false;
  const vec3 point = ray.start + dist * ray.direction;
  const float cross1 =
      glm::dot(glm::cross(vertex_c - vertex_a, point - vertex_a), plane_normal);
  if (cross1 > 0)
    return false;
  const float cross2 =
      glm::dot(glm::cross(vertex_a - vertex_b, point - vertex_b), plane_normal);
  if (cross2 > 0)
    return false;
  const float cross3 =
      glm::dot(glm::cross(vertex_b - vertex_c, point - vertex_c), plane_normal);
  if (cross3 > 0)
    return false;
  return true;
}

std::tuple<float, vec3, vec3> Face::intersect(const Ray &ray,
                                              float max_dist) const {
  const float vn = glm::dot(ray.direction, plane_normal);
  if (fzero(vn))
    return no_hit;
  const float dist = glm::dot(vertex_a - ray.start, plane_normal) / vn;
  if (dist > max_dist || dist < accuracy)
    return no_hit;
  const vec3 point = ray.start + dist * ray.direction;
  if (glm::dot(glm::cross(vertex_c - vertex_a, point - vertex_a),
               plane_normal) > 0)
    return no_hit;
  if (glm::dot(glm::cross(vertex_a - vertex_b, point - vertex_b),
               plane_normal) > 0)
    return no_hit;
  if (glm::dot(glm::cross(vertex_b - vertex_c, point - vertex_c),
               plane_normal) > 0)
    return no_hit;
  if (glm::dot(plane_normal, ray.direction) > 0)
    return {dist, vec3(1.0), -plane_normal};
  return {dist, vec3(1.0), plane_normal};
}

bool Model::intersects(const Ray &ray, float min_dist, float max_dist) const {
  if (!intersectsAABB(ray, min_corner, max_corner, min_dist, max_dist))
    return false;
  for (const auto &face : data) {
    if (face.intersects(ray, min_dist, max_dist))
      return true;
  }
  return false;
}

std::tuple<float, vec3, vec3> Model::intersect(const Ray &ray,
                                               float max_dist) const {
  if (!intersectsAABB(ray, min_corner, max_corner, accuracy, max_dist))
    return no_hit;

  float closest_dist = max_dist;
  bool intersected = false;
  vec3 closest_color = vec3();
  vec3 closest_normal;

  // Returns the closest triangle which the ray intersects
  for (const auto &face : data) {
    const auto &intersect_result = face.intersect(ray, closest_dist);
    const auto &[cur_dist, cur_color, cur_normal] = intersect_result;
    if (cur_dist > accuracy) {
      std::tie(closest_dist, closest_color, closest_normal) = intersect_result;
      intersected = true;
    }
  }

  if (intersected)
    return {closest_dist, closest_color, closest_normal};
  else
    return no_hit;
}
