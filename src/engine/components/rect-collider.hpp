#ifndef RECT_COLLIDER_HPP
#define RECT_COLLIDER_HPP

#include <functional>
#include "../utils/typedefs.hpp"
#include <raylib.h>

class RectCollider {
public:
  using ColliderCallback = std::function<void()>;

private:
  Rectangle collider_;
  ColliderCallback _rightCollideFn;
  ColliderCallback _leftCollideFn;
  ColliderCallback _upCollideFn;
  ColliderCallback _downCollideFn;

public:
  RectCollider(Rectangle collider);
  Rectangle* collider();

public:
  void handleCollsion(const Rectangle* rect);
  void batchHandleCollision(const Vector<Rectangle>* rect);

  RectCollider* addRightCollisionCallback(ColliderCallback callback);
  RectCollider* addLeftCollisionCallback(ColliderCallback callback);
  RectCollider* addDownCollisionCallback(ColliderCallback callback);
  RectCollider* addUpCollisionCallback(ColliderCallback callback);
};

#endif // RECT_COLLIDER_HPP
