
#include "scene.h"

#include "defs.h"
#include <cmath>

Color Scene::intersect(const Ray &ray, size_t depth) const {
  if (depth == 0)
    return background;

  double dist = max_dist;
  Color ambient_color = background;
  bool intersected = false;
  Vector3f normal{0, 0, 0};

  // Find the closest object in the direction the ray is cast
  for (const auto &x : objects) {
    const auto &intersection_result = x->intersect(ray, dist);
    const auto &[tmp_dist, tmp_col, tmp_normal] = intersection_result;
    if (tmp_dist > accuracy && tmp_dist < dist) {
      std::tie(dist, ambient_color, normal) = intersection_result;
      intersected = true;
    }
  }
  if (!intersected)
    return background; // Skip diffuse, specular

  normal = normal.normalize();

  const double bias = 0.001;
  const Vector3f intersection_point = ray.start + dist * ray.direction;

  const Vector3f reflection_direction =
      ray.direction - 2 * (ray.direction.dot(normal)) * normal;
  const Ray reflection_ray{intersection_point, reflection_direction};

  // Recursively find the reflected color
  const Color reflected_color = Scene::intersect(reflection_ray, depth - 1);

  // TODO: replace this with Material values
  const double ambient = 0.1, reflect = 0.2, diffuse = 0.7, specular = 0.25,
               alpha = 100;

  Color diffuse_color{0, 0, 0}, specular_color{0, 0, 0};

  // For each light, check if the light is in direct line-of-sight, if so, add
  // its luminous effect
  for (const auto &light : lights) {
    const Vector3f light_pos = light->getPos();
    const double light_dist = (light_pos - intersection_point).norm();
    const Vector3f Lm = (light_pos - intersection_point).normalize();
    const Vector3f N = normal.normalize();
    const Vector3f V = -1 * ray.direction;
    const Vector3f Rm = 2 * (Lm.dot(N)) * N - Lm;
    const Ray shadow_ray{intersection_point, Lm};
    const double intersection_threshold = accuracy;
    bool obstacles = false;
    const double cosine_angle = Lm.dot(N);
    if (cosine_angle < accuracy)
      continue;
    for (const auto &x : objects) {
      if (x->intersects(shadow_ray, intersection_threshold, light_dist)) {
        obstacles = true;
        break;
      }
    }
    if (!obstacles) {
      const Color light_color = light->getColor(intersection_point);
      diffuse_color = diffuse_color + cosine_angle * light_color;
      if (Rm.dot(V) > 0)
        specular_color = specular_color + pow(Rm.dot(V), alpha) * light_color;
    }
  }
  const Color result = ambient * ambient_color + reflect * reflected_color +
                       diffuse * diffuse_color + specular * specular_color;
  return result.clamp();
}
