#ifndef MOVEABLE_ENTITY_HPP
#define MOVEABLE_ENTITY_HPP

class MoveableEntity {
protected:
  void MoveToDirection();
  void HandleWallCollision();
  void HandleGravity();
protected:
  float move_direction_ = 0.f;
};

#endif // MOVEABLE_ENTITY_HPP
