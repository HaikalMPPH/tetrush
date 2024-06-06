#include <cmath>
#include <iostream>
#include <raylib.h>
#include <raymath.h>

#include "player.hpp"
#include "config.hpp"
#include "game.hpp"


Player::Player(const Game& game)
  : mSpeed {200.f}
  , mVerticalSpeed {0.f}
  , mJumpHeight {-300.f}
  , mPlayerSize {config::kCellSize / 2.f}
  , mPlayerRect {config::kWinW/2.f, 
                 config::kWinH/2.f, 
                 mPlayerSize, 
                 mPlayerSize}
  , mMoveDirection {0.f}
  , mPlayerGravity {20.f}
  , mIsGrounded {false}

  // Note: hardcoded num of rows. be careful when changing it in grid.cpp
  , mrGame {game}
{}

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
    DrawRectangleRec(mPlayerRect, RED);
}

void 
Player::HandleInput() {
  if (IsKeyDown(KEY_A)) {
    mMoveDirection = -1;
  }
  if (IsKeyDown(KEY_D)) {
    mMoveDirection = 1;
  }
  if (IsKeyPressed(KEY_SPACE)) {
    Jump();
  }
}

void
Player::MoveToDirection() {
  mPlayerRect.x += mMoveDirection * mSpeed * GetFrameTime();

  // reset to default after moving.
  mMoveDirection = 0.f;
}

void
Player::HandleGravity() {
  mVerticalSpeed += mPlayerGravity;
  mPlayerRect.y += mVerticalSpeed * GetFrameTime();

  if (mPlayerRect.y + mPlayerSize >= mrGame.groundY) {
    mIsGrounded = true;
    mVerticalSpeed = 0.f;
    mPlayerGravity = 0.f;
    mPlayerRect.y = mrGame.groundY - mPlayerSize;

  }

  // return gravity to normal.
  else {
    mPlayerGravity = 10.f;
  }
}

void
Player::HandleWallCollision() {
  const float left_wall_x = config::kGridOffsetX;
  const float right_wall_x = left_wall_x + config::kCellSize * config::kNumOfCols;

  // Collision with left wall.
  if (mPlayerRect.x <= left_wall_x) {
      mPlayerRect.x = left_wall_x;
  }

  // Collision with right wall.
  else if (mPlayerRect.x + mPlayerSize >= right_wall_x) {
      mPlayerRect.x = right_wall_x - mPlayerSize;
  }
}

void
Player::Jump() {
    if (mIsGrounded) {
        mVerticalSpeed = mJumpHeight;
        mIsGrounded = false;
    }
}


void 
Player::HandleRectCollision(const Rectangle& rect) {
  // player & rect center point
  const Vector2 player_center {
    mPlayerRect.x + mPlayerSize / 2.f,
    mPlayerRect.y + mPlayerSize / 2.f,
  };
  const Vector2 rect_center {
    rect.x + config::kCellSize / 2.f,
    rect.y + config::kCellSize / 2.f,
  };

  // distance between the 2 centers
  const Vector2 center_delta = Vector2Subtract(player_center, rect_center);

  // half widths & heights
  const Vector2 player_halves {
    mPlayerSize / 2.f,
    mPlayerSize / 2.f,
  };
  const Vector2 rect_halves {
    config::kCellSize / 2.f,
    config::kCellSize / 2.f,
  };

  // Seperation distance
  const float dist_x = player_halves.x + rect_halves.x - fabsf(center_delta.x);
  const float dist_y = player_halves.y + rect_halves.y - fabsf(center_delta.y);

  // collide from the sides.
  if (dist_x < dist_y) {
    mPlayerRect.x += dist_x * (center_delta.x / fabsf(center_delta.x));
  }
  // collide from top or bottom
  else {
    mPlayerRect.y += dist_y * (center_delta.y / fabsf(center_delta.y));
    mVerticalSpeed = 0.f;

    // if player is above the rect it's counted as grounded.
    if (player_center.y < rect_center.y) {
      mIsGrounded = true;
    }
  }
}
void
Player::HandleLandedRectCollision() {
  for (Rectangle rect : mrGame.landedBlockRect) {
    if (CheckCollisionRecs(mPlayerRect, rect)) {
      HandleRectCollision(rect);
    }
  }
}
void
Player::HandleCurrentRectCollision() {
  for (Rectangle rect : mrGame.currentBlockRect) {
    if (CheckCollisionRecs(mPlayerRect, rect)) {
      HandleRectCollision(rect);
    }
  }
}

void
Player::HandleDeath() {
  for (Rectangle rect : mrGame.currentBlockRect) {
    if (CheckCollisionRecs(mPlayerRect, rect)) {
      std::cout << "Game Over" << std::endl;
    }
  }
}
