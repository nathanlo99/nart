
#include "scene.h"

#include "common.h"
#include <cmath>

Color Scene::intersect(const Ray &ray, size_t depth) const {
  if (depth == 0)
    return background;

  float dist = max_dist;
  Color ambient_color = background;
  bool intersected = false;
  vec3 normal{0, 0, 0};

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

  normal = glm::normalize(normal);

  const float bias = 0.001;
  const vec3 intersection_point = ray.start + dist * ray.direction;

  const vec3 reflection_direction =
      ray.direction - 2 * glm::dot(ray.direction, normal) * normal;
  const Ray reflection_ray{intersection_point, reflection_direction};

  // Recursively find the reflected color
  const Color reflected_color = Scene::intersect(reflection_ray, depth - 1);

  // TODO: replace this with Material values
  const float ambient = 0.1, reflect = 0.2, diffuse = 0.7, specular = 0.25,
              alpha = 100;

  Color diffuse_color, specular_color;

  // For each light, check if the light is in direct line-of-sight, if so, add
  // its luminous effect
  for (const auto &light : lights) {
    const vec3 light_pos = light->getPos();
    const float light_dist = glm::length(light_pos - intersection_point);
    const vec3 Lm = glm::normalize(light_pos - intersection_point);
    const vec3 N = glm::normalize(normal);
    const vec3 V = -ray.direction;
    const vec3 Rm = 2.0f * glm::dot(Lm, N) * N - Lm;
    const Ray shadow_ray{intersection_point, Lm};
    const float intersection_threshold = accuracy;
    bool obstacles = false;
    const float cosine_angle = glm::dot(Lm, N);
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
      if (glm::dot(Rm, V) > 0)
        specular_color =
            specular_color + pow(glm::dot(Rm, V), alpha) * light_color;
    }
  }
  const Color result = ambient * ambient_color + reflect * reflected_color +
                       diffuse * diffuse_color + specular * specular_color;
  return Color(std::clamp(result.r, 0.0f, 1.0f),
               std::clamp(result.g, 0.0f, 1.0f),
               std::clamp(result.b, 0.0f, 1.0f));
}
