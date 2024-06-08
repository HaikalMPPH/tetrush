#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <raylib.h>

class Game;

class Player {
public: // ctor, dtor, get, set
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
  float _speed;
  float _verticalSpeed;
  const float _jumpHeight;
  const float _playerSize;
  Rectangle _playerRect;
  float _moveDirection;
  float _playerGravity;

  bool _isAlive;
  bool _isGrounded;

  const Game& _gameRef;
};

#endif // PLAYER_HPP
