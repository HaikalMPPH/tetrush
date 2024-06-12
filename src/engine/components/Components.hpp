#ifndef COMPONENTS_HPP
#define COMPONENTS_HPP

#include <raylib.h>
#include <functional>
#include <unordered_map>
#include "../utils/typedefs.hpp"

// ==================== TransformComponent  ========================================
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
// =================================================================================


// ==================== Rect Collider  =========================================
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
// ================================================================================


// ==================== Rect Render  ===============================================
class RectRender {
private:
  const Rectangle* rect_ref_;

public:
  RectRender(const Rectangle* rect);

public:
  void render(Color color);
};
// =================================================================================



// ==================== Input Handler  =============================================
// TODO
// =================================================================================

// ==================== Event Publisher & Event Subscriber =========================
// TODO
class EventSubscriber {
public:
  using NotifyCallback = std::function<void()>;

private:
  std::unordered_map<const char*, NotifyCallback> notify_fn_;

public:
  EventSubscriber();

public:
  EventSubscriber* addNotifyCallback(const char* key, NotifyCallback fn);
  void onNotify(const char* key);
};
// ================================================================================
class EventPublisher {
private:
  using NotifyCallback = EventSubscriber::NotifyCallback;
  Vector<EventSubscriber*> subscribers_;

public:
  EventPublisher();

public:
  EventPublisher* addSubscriber(EventSubscriber* sub);
  EventPublisher* addToAllSubscriberNotifyCallback(const char* key, NotifyCallback fn);
  void notifySubscriber(const char* key);
};

// ================================================================================
#endif // COMPONENTS_HPP
