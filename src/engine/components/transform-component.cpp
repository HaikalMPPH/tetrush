#include "transform-component.hpp"
#include "../../game/config.hpp"


TransformComponent::TransformComponent(Rectangle* rect, float speed)
  : rect_ {rect}
  , speed_ {speed}
  , vertical_speed_ {0.f}
  , gravity_ {config::kGameGravity}
  , is_grounded_ {false}
{}

Rectangle*
TransformComponent::rect() const {
  return rect_;
}
float
TransformComponent::speed() const {
  return speed_;
}
void
TransformComponent::is_grounded(bool b) {
  is_grounded_ = b;
}
bool
TransformComponent::is_grounded() const {
  return is_grounded_;
}
void
TransformComponent::vertical_speed(float vs) {
  vertical_speed_ = vs;
}

void
TransformComponent::moveToDirection(float dir_x) {
  const double delta_time { GetFrameTime() };
  
  rect_->x += dir_x * speed_ * delta_time;
} 

void 
TransformComponent::jump(float y_impulse) {
  if (is_grounded_) {
    vertical_speed_ = y_impulse;
    is_grounded_ = false;
  }
}

void
TransformComponent::handleGravity() {
  vertical_speed_ += gravity_; 
  rect_->y += vertical_speed_ * GetFrameTime();
}
