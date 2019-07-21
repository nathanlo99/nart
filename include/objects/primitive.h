
#ifndef PRIMITIVE_H
#define PRIMITIVE_H

class Primitive: public Object {
public:
  Primitive() {}
  ~Primitive() {}

  virtual bool intersects(const Ray &ray, double min_dist,
                          double max_dist) const = 0;

  virtual std::tuple<Vector3f, Primitive>
  intersect(const Ray &ray, double max_dist) const = 0;
};

#endif
