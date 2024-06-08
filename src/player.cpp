#include <cmath>
#include <iostream>
#include <raylib.h>
#include <raymath.h>

#include "player.hpp"
#include "config.hpp"
#include "game.hpp"


Player::Player(const Game& game)
  : _speed {200.f}
  , _verticalSpeed {0.f}
  , _jumpHeight {-300.f}
  , _playerSize {Config::CellSize / 2.f}
  , _playerRect {Config::WinW/2.f, 
                 Config::WinH/2.f, 
                 _playerSize, 
                 _playerSize}
  , _moveDirection {0.f}
  , _playerGravity {Config::GameGravity}
  , _isAlive {true}
  , _isGrounded {false}
  , _gameRef {game}
{}
Rectangle
Player::player_rect() const {
  return _playerRect;
}


void
Player::Update() {
  // NOTE: Collision are handled after controls or the player won't jump.
  MoveToDirection();
  HandleGravity();

  HandleWallCollision();
  HandleLandedRectCollision();
  HandleCurrentRectCollision();
}

void
Player::Render() {
    DrawRectangleRec(_playerRect, BLUE);
}

void 
Player::HandleInput() {
  if (IsKeyDown(KEY_A)) {
    _moveDirection = -1;
  }
  if (IsKeyDown(KEY_D)) {
    _moveDirection = 1;
  }
  if (IsKeyPressed(KEY_SPACE)) {
    Jump();
  }
}

void
Player::MoveToDirection() {
  _playerRect.x += _moveDirection * _speed * GetFrameTime();

  // reset to default after moving.
  _moveDirection = 0.f;
}

void
Player::HandleGravity() {
  _verticalSpeed += _playerGravity;
  _playerRect.y += _verticalSpeed * GetFrameTime();

  if (
    _playerRect.y + _playerSize >= _gameRef._groundY
    && _isAlive
  ) {
    _isGrounded = true;
    _verticalSpeed = 0.f;
    _playerGravity = 0.f;
    _playerRect.y = _gameRef._groundY - _playerSize;

  }

  // return gravity to normal.
  else {
    _playerGravity = Config::GameGravity;
  }
}

void
Player::HandleWallCollision() {
  const float leftWallX = Config::GridOffsetX;
  const float rightWallX = leftWallX + Config::CellSize * Config::NumOfCols;

  // Collision with left wall.
  if (_playerRect.x <= leftWallX) {
    _playerRect.x = leftWallX;
  }

  // Collision with right wall.
  else if (_playerRect.x + _playerSize >= rightWallX) {
    _playerRect.x = rightWallX - _playerSize;
  }
}

void
Player::Jump() {
  if (_isGrounded && _isAlive) {
    _verticalSpeed = _jumpHeight;
    _isGrounded = false;
  }
}


void 
Player::HandleRectCollision(const Rectangle& rect) {
  // player & rect center point
  const Vector2 player_center {
    _playerRect.x + _playerSize / 2.f,
    _playerRect.y + _playerSize / 2.f,
  };
  const Vector2 rect_center {
    rect.x + Config::CellSize / 2.f,
    rect.y + Config::CellSize / 2.f,
  };

  // distance between the 2 centers
  const Vector2 center_delta = Vector2Subtract(player_center, rect_center);

  // half widths & heights
  const Vector2 player_halves {
    _playerSize / 2.f,
    _playerSize / 2.f,
  };
  const Vector2 rect_halves {
    Config::CellSize / 2.f,
    Config::CellSize / 2.f,
  };

  // Seperation distance
  const float dist_x = player_halves.x + rect_halves.x - fabsf(center_delta.x);
  const float dist_y = player_halves.y + rect_halves.y - fabsf(center_delta.y);

  // collide from the sides.
  if (dist_x < dist_y) {
    _playerRect.x += dist_x * (center_delta.x / fabsf(center_delta.x));
  }
  // collide from top or bottom
  else {
    _playerRect.y += dist_y * (center_delta.y / fabsf(center_delta.y));
    _verticalSpeed = 0.f;

    // if player is above the rect it's counted as grounded.
    if (player_center.y < rect_center.y) {
      _isGrounded = true;
    }
  }
}
void
Player::HandleLandedRectCollision() {
  if (!_isAlive) {
    return;
  }

  for (const Rectangle& rect : _gameRef._landedblockRect) {
    if (CheckCollisionRecs(_playerRect, rect)) {
      HandleRectCollision(rect);
    }
  }
}
void
Player::HandleCurrentRectCollision() {
  if (!_isAlive) {
    return;
  }

  for (const Rectangle& rect : _gameRef._currentBlockRect) {
    if (CheckCollisionRecs(_playerRect, rect)) {
      HandleRectCollision(rect);
    }
  }
}

void
Player::HandleDeath() {
  for (const Rectangle& rect : _gameRef._currentBlockRect) {
    if (CheckCollisionRecs(_playerRect, rect)) {
      std::cout << "Game Over" << std::endl;
      Jump();
      _isAlive = false;
    }
  }
}
