#include <raylib.h>
#include <raymath.h>
#include "rect-collider.hpp"

rect_collider::rect_collider(Rectangle collider)
  : collider_ {collider}
  , right_coll_fn {}
  , left_coll_fn {}
  , up_coll_fn {}
  , down_coll_fn {}
{}

Rectangle*
rect_collider::collider() {
  return &collider_;
}

void
rect_collider::handle_collision(const Rectangle* rect) {
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
        (right_coll_fn != nullptr) ? right_coll_fn() : void();
        
      }
      else {
        (left_coll_fn != nullptr) ? left_coll_fn() : void();
      }
    }
    // collide from top or bottom
    else {
      if (collider_center.y < rect_center.y) {
        (down_coll_fn != nullptr) ? down_coll_fn() : void();
      }
      else {
        (up_coll_fn != nullptr) ? up_coll_fn() : void();
      }

      collider_.y += dist_y * (center_delta.y / fabsf(center_delta.y));
    }
  }
}

void
rect_collider::batch_handle_collision(const vector<Rectangle>* rects) {
  for (Rectangle rect : *rects) {
   handle_collision(&rect);
  }
}

rect_collider*
rect_collider::add_left_collision_callback(collider_callback callback) {
  left_coll_fn = callback;
  return this;
}
rect_collider*
rect_collider::add_down_collision_callback(collider_callback callback) {
  down_coll_fn = callback;
  return this;
}
rect_collider*
rect_collider::add_up_collision_callback(collider_callback callback) {
  up_coll_fn = callback;
  return this;
}
rect_collider*
rect_collider::add_right_collision_callback(collider_callback callback) {
  right_coll_fn = callback;
  return this;
}
