#include "rect-renderer.hpp"


rect_renderer::rect_renderer(const Rectangle* rect)
  : rect_ref_ {rect}
{}

void
rect_renderer::render(Color color) {
  DrawRectangleRec(
      *rect_ref_,
      color
  );
}
