#ifndef RECT_COLLIDER_HPP
#define RECT_COLLIDER_HPP

#include <functional>
#include "../utils/typedefs.hpp"
#include <raylib.h>

class rect_collider {
public:
  using collider_callback = std::function<void()>;

private:
  Rectangle collider_;
  collider_callback right_coll_fn_;
  collider_callback left_coll_fn_;
  collider_callback up_coll_fn_;
  collider_callback down_coll_fn_;

public:
  rect_collider(Rectangle collider);
  Rectangle* collider();

public:
  void handle_collision(const Rectangle* rect);
  void batch_handle_collision(const vector<Rectangle>* rect);

  rect_collider* add_right_collision_callback(collider_callback callback);
  rect_collider* add_left_collision_callback(collider_callback callback);
  rect_collider* add_down_collision_callback(collider_callback callback);
  rect_collider* add_up_collision_callback(collider_callback callback);
};

#endif // RECT_COLLIDER_HPP
