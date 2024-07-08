#ifndef TRANSFORM_COMPONENT_HPP
#define TRANSFORM_COMPONENT_HPP

#include <raylib.h>

class transform_component {
private:
  Rectangle* rect_;
  float speed_;
  float vertical_speed_;
  bool is_grounded_;

public: // ctor, get, set
  transform_component(Rectangle* rect, float speed);
  Rectangle* rect() const; // get
  float speed() const; // get

  void is_grounded(bool b); // set
  bool is_grounded() const; // get
  void vertical_speed(float vs); // set

public: // methods
  void move_to_direction(float dir_x);
  void handle_gravity();
  void jump(float y_impulse);
};

#endif // TRANSFORM_COMPONENT_HPP
