#ifndef RECT_RENDERER_HPP
#define RECT_RENDERER_HPP

#include <raylib.h>

class rect_renderer {
private:
  const Rectangle* rect_ref_;

public:
  rect_renderer(const Rectangle* rect);

public:
  void render(Color color);
};

#endif // RECT_RENDERER_HPP
