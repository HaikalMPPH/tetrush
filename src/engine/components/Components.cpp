#include "Components.hpp"
#include "../../game/config.hpp"

#include <cmath>
#include <iostream>
#include <raylib.h>
#include <raymath.h>

// ==================== TransformComponent  ========================================
TransformComponent::TransformComponent(Rectangle* rect, float speed)
  : rect_ {rect}
  , speed_ {speed}
  , vertical_speed_ {0.f}
  , gravity_ {Config::kGameGravity}
  , is_grounded_ {true}
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
    std::cout << "JUMP!" << std::endl;
    vertical_speed_ = y_impulse;
    is_grounded_ = false;
  }
}

void
TransformComponent::handleGravity() {
  vertical_speed_ += gravity_; 
  rect_->y += vertical_speed_ * GetFrameTime();

  if (
    rect_->y + rect_->height >= Config::kGrondY
  ) {
    is_grounded_ = true;
    vertical_speed_ = 0.f;
    gravity_ = 0.f;
    rect_->y = Config::kGrondY - rect_->height;

  }

  // return gravity to normal.
  else {
    gravity_ = Config::kGameGravity;
  }
}
// =================================================================================


// ==================== Rect Collider  =========================================
RectCollider::RectCollider(Rectangle collider)
  : collider_ {collider}
  , _rightCollideFn {}
  , _leftCollideFn {}
  , _upCollideFn {}
  , _downCollideFn {}
{}

Rectangle*
RectCollider::collider() {
  return &collider_;
}

void
RectCollider::handleCollsion(const Rectangle* rect) {
  if (CheckCollisionRecs(collider_, *rect)) {
    // player & rect center point
    const Vector2 collider_center {
      collider_.x + collider_.width / 2.f,
      collider_.y + collider_.height / 2.f,
    };
    const Vector2 rect_center {
      rect->x + rect->width / 2.f,
      rect->y + rect->height / 2.f,
    };

    // distance between the 2 centers
    const Vector2 center_delta = Vector2Subtract(collider_center, rect_center);

    // half widths & heights
    const Vector2 collider_halves {
      collider_.width / 2.f,
      collider_.height / 2.f,
    };
    const Vector2 rect_halves {
      rect->width / 2.f,
      rect->height / 2.f,
    };

    // Seperation distance
    const float dist_x = collider_halves.x + rect_halves.x - fabsf(center_delta.x);
    const float dist_y = collider_halves.y + rect_halves.y - fabsf(center_delta.y);

    // collide from the sides.
    if (dist_x < dist_y) {
      collider_.x += dist_x * (center_delta.x / fabsf(center_delta.x));

      if (collider_center.x < rect_center.x) {
        (_rightCollideFn != nullptr) ? _rightCollideFn() : void();
        
      }
      else {
        (_leftCollideFn != nullptr) ? _leftCollideFn() : void();
      }
    }
    // collide from top or bottom
    else {
      if (collider_center.y < rect_center.y) {
        (_downCollideFn != nullptr) ? _downCollideFn() : void();
      }
      else {
        (_upCollideFn != nullptr) ? _upCollideFn() : void();
      }

      collider_.y += dist_y * (center_delta.y / fabsf(center_delta.y));
    }
  }
}

void
RectCollider::batchHandleCollision(const Vector<Rectangle>* rects) {
  for (Rectangle rect : *rects) {
   handleCollsion(&rect);
  }
}

RectCollider*
RectCollider::addLeftCollisionCallback(ColliderCallback callback) {
  _leftCollideFn = callback;
  return this;
}
RectCollider*
RectCollider::addDownCollisionCallback(ColliderCallback callback) {
  _downCollideFn = callback;
  return this;
}
RectCollider*
RectCollider::addUpCollisionCallback(ColliderCallback callback) {
  _upCollideFn = callback;
  return this;
}
RectCollider*
RectCollider::addRightCollisionCallback(ColliderCallback callback) {
  _rightCollideFn = callback;
  return this;
}
// ======================================================================================


// ==================== Rect Render  ===========================================
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
// =================================================================================
