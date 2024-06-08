#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <raylib.h>

class Game;

class Enemy {
public:
  Enemy(const Game& rGame);

  void Render();
  void Update();

  void HandleDeath();

private:
  void MoveToPlayer();
  void HandleGravity();
  void HandleWallCollision(); // TODO
  void Jump();                // TODO

  void HandleRectCollision(const Rectangle& rect);
  void HandleLandedRectCollision();
  void HandleCurrentRectCollision();


private:
  const Game& game_ref_;
  float move_direction_;
  float enemy_size_;
  Rectangle enemy_rect_;
  float enemy_gravity_;
  const float jump_height_;
  float speed_;
  float vertical_speed_;

  // Enemy only allowed to jump once every cooldown.
  bool is_jumpable_;
  const float kJumpCooldown;
  float current_jump_cooldown_;

  bool is_alive_;
  bool is_grounded_;
};

#endif // ENEMY_HPP
