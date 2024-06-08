#include <iostream>
#include <raylib.h>
#include <raymath.h>

#include "enemy.hpp"
#include "game.hpp"
#include "config.hpp"

Enemy::Enemy(const Game& game, int xPos) 
  : _gameRef (game)
  , _moveDirection (0.f)
  , _enemySize (Config::CellSize / 2.f)
  , _enemyRect ({
      (float)xPos, 
      -10.f,
      _enemySize,
      _enemySize,
    })
  , _enemyGravity (Config::GameGravity)
  , _jumpHeight (-250.f)
  , _speed (75.f)
  , _verticalSpeed (0.f)
  , _JumpCooldown (1.f)
  , _currentJumpCooldown (_JumpCooldown)
  , _isAlive (true)
  , _isGrounded (false)
{}

void
Enemy::Render() {
  DrawRectangleRec(_enemyRect, RED);
}

void 
Enemy::Update() {
  HandleGravity();
  MoveToPlayer();

  HandleLandedRectCollision();
  HandleCurrentRectCollision();

  // NOTE: Moved Jump() here to allow the enemy to jump on top of tetrominos.
  Jump();
}

void
Enemy::MoveToPlayer() {
  const float enemy_x = _gameRef._player.player_rect().x;
  if ( enemy_x < _enemyRect.x) {
    _moveDirection = -1.f;
  }
  else {
    _moveDirection = 1.f;
  }

  _enemyRect.x += _moveDirection * _speed * GetFrameTime();
}

void
Enemy::HandleGravity() {
  _verticalSpeed += _enemyGravity;
  _enemyRect.y += _verticalSpeed * GetFrameTime();

  if (
    _enemyRect.y + _enemySize >= _gameRef._groundY
    && _isAlive
  ) {
    _isGrounded = true;
    _verticalSpeed = 0.f;
    _enemyGravity = 0.f;
    _enemyRect.y = _gameRef._groundY - _enemySize;

  }

  // return gravity to normal.
  else {
    _enemyGravity = Config::GameGravity;
  }
}
void 
Enemy::Jump() {
  if (
      _isGrounded
      && _isAlive
      && _currentJumpCooldown <= 0
  ) {
    _verticalSpeed = _jumpHeight;
    _isGrounded = false;
    _currentJumpCooldown = _JumpCooldown;
  }

  _currentJumpCooldown -= GetFrameTime();
}

void
Enemy::HandleRectCollision(const Rectangle& rect) {
  const Vector2 enemy_center {
    _enemyRect.x + _enemySize / 2.f,
    _enemyRect.y + _enemySize / 2.f,
  };
  const Vector2 rect_center {
    rect.x + Config::CellSize / 2.f,
    rect.y + Config::CellSize / 2.f,
  };

  const Vector2 center_delta = Vector2Subtract(enemy_center, rect_center);

  const Vector2 enemy_halves {
    _enemySize / 2.f,
    _enemySize / 2.f,
  };
  const Vector2 rect_halves {
    Config::CellSize / 2.f,
    Config::CellSize / 2.f,
  };

  const float dist_x = enemy_halves.x + rect_halves.x - fabsf(center_delta.x);
  const float dist_y = enemy_halves.y + rect_halves.y - fabsf(center_delta.y);

  if (dist_x < dist_y) {
    _enemyRect.x += dist_x * (center_delta.x / fabsf(center_delta.x));
  }
  else {
    _enemyRect.y += dist_y * (center_delta.y / fabsf(center_delta.y));
    _verticalSpeed = 0.f;

    if (enemy_center.y < rect_center.y) {
      _isGrounded = true;
    }
  }
}
void
Enemy::HandleLandedRectCollision() {
  if (!_isAlive) {
    return;
  }

  for (const Rectangle& rect : _gameRef._landedblockRect) {
    if (CheckCollisionRecs(_enemyRect, rect)) {
      HandleRectCollision(rect);
    }
  }
}
void
Enemy::HandleCurrentRectCollision() {
  if (!_isAlive) {
    return;
  }

  for (const Rectangle& rect : _gameRef._currentBlockRect) {
    if (CheckCollisionRecs(_enemyRect, rect)) {
      HandleRectCollision(rect);
    }
  }
}
void
Enemy::HandleDeath() {
  for (const Rectangle& rect : _gameRef._currentBlockRect) {
    if (CheckCollisionRecs(_enemyRect, rect)) {
      std::cout << "enemy killed" << std::endl;
      _isAlive = false;
    }
  }
}
