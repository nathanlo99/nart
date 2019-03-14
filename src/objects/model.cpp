
#include "objects/model.h"

#include "color.h"
#include "defs.h"
#include "ray.h"
#include "util.h"

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
  data = loadOBJ(obj_file_name);
}

bool Face::intersects(const Ray &ray, double min_dist, double max_dist) const {
  const double vn = ray.direction.dot(plane_normal);
  if (fzero(vn))
    return false;
  const double dist = (vertex_a - ray.start).dot(plane_normal) / vn;
  if (dist < min_dist || dist > max_dist)
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
  if (dist > max_dist || dist < accuracy)
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
  Vector3f normal = plane_normal;
  if (normal.dot(ray.direction) > 0)
    normal = -1 * plane_normal;
  return {dist, Color::WHITE, normal};
}

bool Model::intersects(const Ray &ray, double min_dist, double max_dist) const {
  for (const auto &face : data) {
    if (face.intersects(ray, min_dist, max_dist))
      return true;
  }
  return false;
}

std::tuple<double, Color, Vector3f> Model::intersect(const Ray &ray,
                                                     double max_dist) const {
  double closest_dist = 10000.0, cur_dist;
  bool intersected = false;
  Color closest_color = Color::BLACK, cur_color;
  Vector3f closest_normal, cur_normal;

  for (const auto &face : data) {
    const auto &intersect_result = face.intersect(ray, closest_dist);
    std::tie(cur_dist, cur_color, cur_normal) = intersect_result;
    if (cur_dist > accuracy && cur_dist < max_dist) {
      std::tie(closest_dist, closest_color, closest_normal) = intersect_result;
      intersected = true;
    }
  }

  if (intersected)
    return {closest_dist, closest_color, closest_normal};
  else
    return {-1, {0, 0, 0}, {0, 0, 0}};
}
