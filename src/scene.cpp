
#include "scene.h"

#include "defs.h"
#include <cmath>

vec3 Scene::intersect(const Ray &ray, size_t depth) const {
  if (depth == 0)
    return background;

  float dist = max_dist;
  vec3 ambient_color = background;
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

  normal = normal.normalize();

  const float bias = 0.001f;
  const vec3 intersection_point = ray.start + dist * ray.direction;

  const vec3 reflection_direction =
      ray.direction - 2 * (ray.direction.dot(normal)) * normal;
  const Ray reflection_ray{intersection_point, reflection_direction};

  // Recursively find the reflected color
  const vec3 reflected_color = Scene::intersect(reflection_ray, depth - 1);

  // TODO: replace this with Material values
  const float ambient = 0.1f, reflect = 0.2f, diffuse = 0.7f, specular = 0.25f,
              alpha = 100.0f;

  vec3 diffuse_color, specular_color;

  // For each light, check if the light is in direct line-of-sight, if so, add
  // its luminous effect
  for (const auto &light : lights) {
    const vec3 light_pos = light->getPos();
    const float light_dist = (light_pos - intersection_point).norm();
    const vec3 Lm = (light_pos - intersection_point).normalize();
    const vec3 N = normal.normalize();
    const vec3 V = -1 * ray.direction;
    const vec3 Rm = 2 * (Lm.dot(N)) * N - Lm;
    const Ray shadow_ray{intersection_point, Lm};
    const float intersection_threshold = accuracy;
    bool obstacles = false;
    const float cosine_angle = Lm.dot(N);
    if (cosine_angle < accuracy)
      continue;
    for (const auto &x : objects) {
      if (x->intersects(shadow_ray, intersection_threshold, light_dist)) {
        obstacles = true;
        break;
      }
    }
    if (!obstacles) {
      const vec3 light_color = light->getvec3(intersection_point);
      diffuse_color = diffuse_color + cosine_angle * light_color;
      if (Rm.dot(V) > 0)
        specular_color = specular_color + pow(Rm.dot(V), alpha) * light_color;
    }
  }
  const vec3 result = ambient * ambient_color + reflect * reflected_color +
                      diffuse * diffuse_color + specular * specular_color;
  return vec3(std::clamp(result.r, 0.0f, 1.0f),
              std::clamp(result.g, 0.0f, 1.0f),
              std::clamp(result.b, 0.0f, 1.0f));
}
