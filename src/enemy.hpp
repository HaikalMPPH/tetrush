#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <raylib.h>

class Game;

class Enemy {
public:
  Enemy(const Game& rGame);

  void Render();
  void Update();

private:
  void MoveToPlayer();
  void HandleGravity();
  void ChasePlayer();
  void Jump();

  void HandleRectCollision(const Rectangle& rect);
  void HandleLandedRectCollision();
  void HandleCurrentRectCollision();

  void HandleDeath();

private:
  const Game& game_ref_;
  float move_direction_;
  float enemy_size_;
  Rectangle enemy_rect_;
  float enemy_gravity_;
  float speed_;
  float vertical_speed_;
};

#endif // ENEMY_HPP
