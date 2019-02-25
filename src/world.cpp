
#include "world.h"

#include "defs.h"
#include <cmath>

Color World::intersect(const Ray &ray, size_t depth) const {
  if (depth == 0)
    return background;

  double dist = max_dist;
  Color ambient_color = background;
  bool intersected = false;
  Vector3f normal{0, 0, 0};

  for (const auto &x : objects) {
    double tmp_dist;
    Color tmp_col;
    Vector3f tmp_normal{0, 0, 0};
    const auto &intersection_result = x->intersect(ray, dist);
    std::tie(tmp_dist, tmp_col, tmp_normal) = intersection_result;
    if (tmp_dist > accuracy && tmp_dist < dist) {
      std::tie(dist, ambient_color, normal) = intersection_result;
      intersected = true;
    }
  }
  if (!intersected)
    return background; // Skip diffuse, specular

  const Vector3f intersection_point = ray.start + dist * ray.direction;
  const double ambient = 0.1, diffuse = 0.7, specular = 0.3, alpha = 100;

  Color diffuse_color{0, 0, 0}, specular_color{0, 0, 0};

  for (const auto &light : lights) {
    const Vector3f Lm = (light->getPos() - intersection_point).normalize();
    const Vector3f N = normal.normalize();
    const Vector3f V = -1 * ray.direction;
    const Vector3f Rm = 2 * (Lm.dot(N)) * N - Lm;
    const Ray shadow_ray{intersection_point, Lm};
    const double light_dist = (light->getPos() - intersection_point).norm();
    if (Lm.dot(N) <= 0)
      continue;
    bool obstacles = false;
    // int index = 0;
    // for (const auto &x : objects) {
    //   if (x->intersects(shadow_ray, light_dist)) {
    //     obstacles = true;
    //     break;
    //   }
    //   ++index;
    // }
    // obstacles = false;
    if (!obstacles) {
      const Color light_color = light->getColor(intersection_point);
      // INFO("Lm.N");
      if (Lm.dot(N) > 0)
        diffuse_color = diffuse_color + Lm.dot(N) * light_color;
      if (Rm.dot(V) > 0)
        specular_color = specular_color + pow(Rm.dot(V), alpha) * light_color;
    } else {
      // INFO("S");
    }
  }

  const Color result = ambient * ambient_color + diffuse * diffuse_color +
                       specular * specular_color;
  return result.clamp();
}
