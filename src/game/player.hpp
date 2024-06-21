#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <raylib.h>

#include "../engine/components/rect-collider.hpp"
#include "../engine/components/rect-renderer.hpp"
#include "../engine/components/transform-component.hpp"
#include "../engine/components/subscriber-publisher.hpp"

class Game;

class Player {
private:
  RectCollider collider_;
  RectRender renderer_;
  TransformComponent transform_;
  EventSubscriber subscriber_;
  EventPublisher player_event_publisher_;

  bool is_alive_;

  Game* game_;

public: // ctor, dtor, get, set
  Player(Game* game);
  Rectangle* collider();
  EventSubscriber* subscriber();

public:
  void update();
  void render();

  void handleInput();
  void death();
  void handleDeath();

private:

};

#endif // PLAYER_HPP
