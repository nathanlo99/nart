
#ifndef WORLD_H
#define WORLD_H

#include "color.h"
#include "objects/object.h"
#include "ray.h"

#include <memory>
#include <vector>

class World {
  std::vector<std::unique_ptr<Object>> objects;
  double max_dist = 10000.0;
  Color background = Color::BLACK;

public:
  World() {}
  explicit World(std::vector<std::unique_ptr<Object>> &&objects)
      : objects{std::move(objects)} {}
  ~World() {}

  void addObject(std::unique_ptr<Object> &&object) {
    objects.push_back(std::move(object));
  }

  Color intersect(const Ray &ray, size_t depth) const;
};

#endif
