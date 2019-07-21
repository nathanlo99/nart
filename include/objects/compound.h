
#ifndef COMPOUND_H
#define COMPOUND_H

class Compound: public Object {
  std::vector<Object*> objects;

public:
  Compound() {}
  ~Compound() {}

  virtual bool intersects(const Ray &ray, double min_dist,
                          double max_dist) const = 0;

  virtual std::tuple<Vector3f, Primitive>
  intersect(const Ray &ray, double max_dist) const = 0;
};

#endif
