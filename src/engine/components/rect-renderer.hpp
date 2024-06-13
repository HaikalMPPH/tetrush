#ifndef RECT_RENDERER_HPP
#define RECT_RENDERER_HPP

#include <raylib.h>

class RectRender {
private:
  const Rectangle* rect_ref_;

public:
  RectRender(const Rectangle* rect);

public:
  void render(Color color);
};

#endif // RECT_RENDERER_HPP
