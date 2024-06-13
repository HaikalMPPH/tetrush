#include "rect-renderer.hpp"


RectRender::RectRender(const Rectangle* rect)
  : rect_ref_ {rect}
{}

void
RectRender::render(Color color) {
  DrawRectangleRec(
      *rect_ref_,
      color
  );
}
