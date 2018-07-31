
#ifndef RAYTRACER_H
#define RAYTRACER_H

#include <string>

class Raytracer {
private:
  /* data */

public:
  Raytracer(std::string fileName);
  Raytracer(const Raytracer &other);
  virtual ~Raytracer();
};

#endif
