#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <raylib.h>

class Game;

class Enemy {
public:
  Enemy(const Game& rGame, int xPos);

  void Render();
  void Update();

  void HandleDeath();

private:
  void MoveToPlayer();
  void HandleGravity();
  void HandleWallCollision();
  void Jump();               

  void HandleRectCollision(const Rectangle& rect);
  void HandleLandedRectCollision();
  void HandleCurrentRectCollision();


private:
  const Game& _gameRef;
  float _moveDirection;
  float _enemySize;
  Rectangle _enemyRect;
  float _enemyGravity;
  const float _jumpHeight;
  float _speed;
  float _verticalSpeed;

  // Enemy only allowed to jump once every cooldown.
  const float _JumpCooldown;
  float _currentJumpCooldown;

  bool _isAlive;
  bool _isGrounded;
};

#endif // ENEMY_HPP
