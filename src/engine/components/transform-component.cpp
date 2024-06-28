#include "transform-component.hpp"
#include "../../game/config.hpp"


transform_component::transform_component(Rectangle* rect, float speed)
  : rect_ {rect}
  , speed_ {speed}
  , vertical_speed_ {0.f}
  , gravity_ {config::game_gravity}
  , is_grounded_ {false}
{}

Rectangle*
transform_component::rect() const {
  return rect_;
}
float
transform_component::speed() const {
  return speed_;
}
void
transform_component::is_grounded(bool b) {
  is_grounded_ = b;
}
bool
transform_component::is_grounded() const {
  return is_grounded_;
}
void
transform_component::vertical_speed(float vs) {
  vertical_speed_ = vs;
}

void
transform_component::move_to_direction(float dir_x) {
  const double delta_time { GetFrameTime() };
  
  rect_->x += dir_x * speed_ * delta_time;
} 

void 
transform_component::jump(float y_impulse) {
  if (is_grounded_) {
    vertical_speed_ = y_impulse;
    is_grounded_ = false;
  }
}

void
transform_component::handle_gravity() {
  vertical_speed_ += gravity_; 
  rect_->y += vertical_speed_ * GetFrameTime();
}
