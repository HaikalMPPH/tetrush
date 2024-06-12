#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <raylib.h>

#include "../engine/components/Components.hpp"

class Game;

class Enemy {
public:
  Enemy(Game* game, int xPos);
  ~Enemy();

  void render();
  void update();

  // The int will be used as a score.
  int handleDeath();

private:
  void moveToPlayer();
  void jump();               


private:
  Game* game_;
  RectCollider collider_;
  RectRender renderer_;
  TransformComponent transform_;

  // Enemy only allowed to jump once every cooldown.
  const float jump_cooldown;
  float current_jump_cooldonw_;

  bool is_alive_;
  bool marked_for_delete_;
};

#endif // ENEMY_HPP
