#ifndef RENDERER_H
#define RENDERER_H

class Renderer {
public:
  Renderer() noexcept {}
  virtual ~Renderer() noexcept {}

  virtual Image render(const Camera &camera, const World &world) = 0;
};

#endif
