#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <raylib.h>

class Game;

class Player {
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

private:
  float mSpeed;
  float mVerticalSpeed;
  float mJumpHeight;
  float mPlayerSize;
  Rectangle mPlayerRect;
  float mMoveDirection;
  float mPlayerGravity;

  bool mIsGrounded;

  const Game& mrGame;
};

#endif // PLAYER_HPP
