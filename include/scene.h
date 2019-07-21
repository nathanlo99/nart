
#ifndef SCENE_H
#define SCENE_H

#include "color.h"
#include "lights/light.h"
#include "objects/object.h"
#include "ray.h"

#include <memory>
#include <vector>

// Represents a 3D scene, containing objects and lights
class Scene {
  std::vector<std::unique_ptr<Object>> objects;
  std::vector<std::unique_ptr<Light>> lights;

  // The rendering distance
  // TODO: perhaps this is more suited for RayTracer?
  double max_dist = 10000.0;
  // The background color, used when a ray does not intersect any objects
  Color background = Color::BLACK;

public:
  Scene() {}
  explicit Scene(std::vector<std::unique_ptr<Object>> &&objects,
                 std::vector<std::unique_ptr<Light>> &&lights)
      : objects{std::move(objects)}, lights{std::move(lights)} {}
  ~Scene() {}

  void addObject(std::unique_ptr<Object> &&object) {
    objects.push_back(std::move(object));
  }

  void addLight(std::unique_ptr<Light> &&light) {
    lights.push_back(std::move(light));
  }

  // Returns the color resulting from tracing the specified ray in this scene,
  // with max recursive depth 'depth'
  Color intersect(const Ray &ray, size_t depth) const;
};

#endif
