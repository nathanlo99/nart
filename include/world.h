
#ifndef WORLD_H
#define WORLD_H

#include "color.h"
#include "objects/object.h"
#include "ray.h"

#include <memory>
#include <vector>

class World {
  std::vector<std::unique_ptr<Object>> objects;

public:
  World() : objects{} {}
  explicit World(std::vector<std::unique_ptr<Object>> &&objects)
      : objects{std::move(objects)} {}
  ~World() {}

  void addObject(std::unique_ptr<Object> &&object) {
    objects.push_back(std::move(object));
  }

  std::pair<Color, std::vector<Ray>> intersect(const Ray &ray) const;
};

#endif
