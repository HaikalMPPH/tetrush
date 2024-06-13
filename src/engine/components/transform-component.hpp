#ifndef TRANSFORM_COMPONENT_HPP
#define TRANSFORM_COMPONENT_HPP

#include <raylib.h>

class TransformComponent {
private:
  Rectangle* rect_;
  float speed_;
  float vertical_speed_;
  float gravity_;
  bool is_grounded_;

public: // ctor, get, set
  TransformComponent(Rectangle* rect, float speed);
  Rectangle* rect() const; // get
  float speed() const; // get

  void is_grounded(bool b); // set
  bool is_grounded() const; // get
  void vertical_speed(float vs); // set

public: // methods
  void moveToDirection(float dir_x);
  void handleGravity();
  void jump(float y_impulse);
};

#endif // TRANSFORM_COMPONENT_HPP
