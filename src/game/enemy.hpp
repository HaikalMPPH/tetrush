#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <raylib.h>

#include "../engine/components/rect-collider.hpp"
#include "../engine/components/rect-renderer.hpp"
#include "../engine/components/transform-component.hpp"
#include "../engine/components/subscriber-publisher.hpp"

class Game;

class Enemy {
public:
  Enemy(Game* game, int xPos);
  ~Enemy();

  EventSubscriber* subscriber();

public:
  void render();
  void update();
  // The int will be used as a score.

private:
  void moveToPlayer();
  void jump();
  void death();
  void handleDeath();

public:
  bool marked_for_delete;

private:
  Game* game_;
  RectCollider collider_;
  RectRender renderer_;
  TransformComponent transform_;
  EventSubscriber subscriber_;
  EventPublisher enemy_event_publisher_;

  // Enemy only allowed to jump once every cooldown.
  const float jump_cooldown;
  float current_jump_cooldonw_;

  bool is_alive_;
};

#endif // ENEMY_HPP
