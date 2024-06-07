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

  // handle_death:
  // 1. key k is pressed
  // 2. danger x is calculated. That is, the min x position of current_block/projection and
  //    it's max x position. This is handled in the update
  void HandleDeath();

private:
  float speed_;
  float vertical_speed_;
  float jump_height_;
  float player_size_;
  Rectangle player_rect_;
  float move_direction_;
  float player_gravity_;

  bool is_grounded_;

  const Game& game_ref_;
};

#endif // PLAYER_HPP
