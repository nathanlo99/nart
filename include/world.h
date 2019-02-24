
#ifndef WORLD_H
#define WORLD_H

#include "color.h"
#include "lights/light.h"
#include "objects/object.h"
#include "ray.h"

#include <memory>
#include <vector>

class World {
  std::vector<std::unique_ptr<Object>> objects;
  std::vector<std::unique_ptr<Light>> lights;

  double max_dist = 10000.0;
  Color background = Color::BLACK;

public:
  World() {}
  explicit World(std::vector<std::unique_ptr<Object>> &&objects,
                 std::vector<std::unique_ptr<Light>> &&lights)
      : objects{std::move(objects)}, lights{std::move(lights)} {}
  ~World() {}

  void addObject(std::unique_ptr<Object> &&object) {
    objects.push_back(std::move(object));
  }

  void addLight(std::unique_ptr<Light> &&light) {
    lights.push_back(std::move(light));
  }

  Color intersect(const Ray &ray, size_t depth) const;
};

#endif
