#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <raylib.h>

class Game;

class Player {
public:
  Player(const Game& game);
  Rectangle player_rect() const;

public:

  void Update();
  void Render();

  void HandleInput();

  void MoveToDirection();
  void HandleGravity();
  void HandleWallCollision();
  void Jump();

  void HandleRectCollision(const Rectangle& rect);
  void HandleLandedRectCollision();
  void HandleCurrentRectCollision();

  void HandleDeath();

private:
  float speed_;
  float vertical_speed_;
  const float jump_height_;
  const float player_size_;
  Rectangle player_rect_;
  float move_direction_;
  float player_gravity_;

  bool is_alive_;
  bool is_grounded_;

  const Game& game_ref_;
};

#endif // PLAYER_HPP
