
#include "scene.h"

#include "common.h"
#include <cmath>

vec3 Scene::intersect(const Ray &ray, size_t depth) const {
  if (depth == 0)
    return background;

  float dist = max_dist;
  vec3 ambient_colour = background;
  bool intersected = false;
  vec3 normal = vec3();

  // Find the closest object in the direction the ray is cast
  for (const auto &x : objects) {
    const auto &intersection_result = x->intersect(ray, dist);
    const auto &[tmp_dist, tmp_col, tmp_normal] = intersection_result;
    if (tmp_dist > accuracy && tmp_dist < dist) {
      std::tie(dist, ambient_colour, normal) = intersection_result;
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

  // Recursively find the reflected colour
  const vec3 reflected_colour = Scene::intersect(reflection_ray, depth - 1);

  // TODO: replace this with Material values
  const float ambient = 0.1, reflect = 0.2, diffuse = 0.7, specular = 0.25,
              alpha = 100;

  vec3 diffuse_colour = vec3(), specular_colour = vec3();

  // For each light, check if the light is in direct line-of-sight, if so, add
  // its luminous effect
  for (const auto &light : lights) {
    const vec3 light_pos = light->get_position();
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
      const vec3 light_colour = light->get_colour(intersection_point);
      diffuse_colour = diffuse_colour + cosine_angle * light_colour;
      if (glm::dot(Rm, V) > 0)
        specular_colour += glm::pow(glm::dot(Rm, V), alpha) * light_colour;
    }
  }
  const vec3 result = ambient * ambient_colour + reflect * reflected_colour +
                      diffuse * diffuse_colour + specular * specular_colour;
  return vec3(std::clamp(result.r, 0.0f, 1.0f),
              std::clamp(result.g, 0.0f, 1.0f),
              std::clamp(result.b, 0.0f, 1.0f));
}
