#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <raylib.h>

#include "../engine/components/rect-collider.hpp"
#include "../engine/components/rect-renderer.hpp"
#include "../engine/components/transform-component.hpp"
#include "../engine/components/subscriber-publisher.hpp"

class game;

class enemy {
public:
  enemy(::game* game, int xPos);
  ~enemy();

  ::event_subscriber* subscriber();

public:
  void render();
  void update();
  // The int will be used as a score.

private:
  void move_to_player();
  void jump();
  void death();
  void handle_death();

public:
  bool marked_for_delete;

private:
  ::game* game_;
  ::rect_collider collider_;
  ::rect_renderer renderer_;
  ::transform_component transform_;
  ::event_subscriber subscriber_;
  ::event_publisher enemy_event_publisher_;

  // Enemy only allowed to jump once every cooldown.
  const float jump_cooldown;
  float current_jump_cooldonw_;

  bool is_alive_;
};

#endif // ENEMY_HPP
