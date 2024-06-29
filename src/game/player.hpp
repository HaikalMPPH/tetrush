#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <raylib.h>

#include "../engine/components/rect-collider.hpp"
#include "../engine/components/rect-renderer.hpp"
#include "../engine/components/transform-component.hpp"
#include "../engine/components/subscriber-publisher.hpp"

class game;

class player {
private:
  ::rect_collider collider_;
  ::rect_renderer renderer_;
  ::transform_component transform_;
  ::event_subscriber subscriber_;
  ::event_publisher player_event_publisher_;

  bool is_alive_;

  ::game* game_;

public: // ctor, dtor, get, set
  player(::game* game);
  ~player();

  ::Rectangle* collider();
  ::event_subscriber* subscriber();

public:
  void update();
  void render();

  void handle_input();
  void death();
  void handle_death();
};

#endif // PLAYER_HPP
