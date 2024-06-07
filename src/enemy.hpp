#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <raylib.h>

class Game;

class Enemy {
public:
  Enemy(const Game& rGame);

  void Render();

private:
  void MoveToDirection();
  void HandleGravity();

private:
  const Game& game_ref_;
  float move_direction_;
  Rectangle enemy_rect_;
};

#endif // ENEMY_HPP
