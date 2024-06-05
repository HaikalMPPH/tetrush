#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <raylib.h>

class Game;

class Player {
public:
  float speed;
  float vertical_speed;
  float jump_height;
  float player_size;
  Rectangle player_rect;
  float move_direction_x;
  float player_gravity;

  bool is_grounded;

  const Game& game;

public:
  Player(const Game& game);

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
};

#endif // PLAYER_HPP
