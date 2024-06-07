#include <cmath>
#include <iostream>
#include <raylib.h>
#include <raymath.h>

#include "player.hpp"
#include "config.hpp"
#include "game.hpp"


Player::Player(const Game& game)
  : speed_ {200.f}
  , vertical_speed_ {0.f}
  , jump_height_ {-300.f}
  , player_size_ {config::kCellSize / 2.f}
  , player_rect_ {config::kWinW/2.f, 
                 config::kWinH/2.f, 
                 player_size_, 
                 player_size_}
  , move_direction_ {0.f}
  , player_gravity_ {config::kGameGravity}
  , is_grounded_ {false}

  // Note: hardcoded num of rows. be careful when changing it in grid.cpp
  , game_ref_ {game}
{}
Rectangle
Player::player_rect() const {
  return player_rect_;
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
    DrawRectangleRec(player_rect_, BLUE);
}

void 
Player::HandleInput() {
  if (IsKeyDown(KEY_A)) {
    move_direction_ = -1;
  }
  if (IsKeyDown(KEY_D)) {
    move_direction_ = 1;
  }
  if (IsKeyPressed(KEY_SPACE)) {
    Jump();
  }
}

void
Player::MoveToDirection() {
  player_rect_.x += move_direction_ * speed_ * GetFrameTime();

  // reset to default after moving.
  move_direction_ = 0.f;
}

void
Player::HandleGravity() {
  vertical_speed_ += player_gravity_;
  player_rect_.y += vertical_speed_ * GetFrameTime();

  if (player_rect_.y + player_size_ >= game_ref_.ground_y) {
    is_grounded_ = true;
    vertical_speed_ = 0.f;
    player_gravity_ = 0.f;
    player_rect_.y = game_ref_.ground_y - player_size_;

  }

  // return gravity to normal.
  else {
    player_gravity_ = config::kGameGravity;
  }
}

void
Player::HandleWallCollision() {
  const float leftWallX = config::kGridOffsetX;
  const float rightWallX = leftWallX + config::kCellSize * config::kNumOfCols;

  // Collision with left wall.
  if (player_rect_.x <= leftWallX) {
    player_rect_.x = leftWallX;
  }

  // Collision with right wall.
  else if (player_rect_.x + player_size_ >= rightWallX) {
    player_rect_.x = rightWallX - player_size_;
  }
}

void
Player::Jump() {
  if (is_grounded_) {
    vertical_speed_ = jump_height_;
    is_grounded_ = false;
  }
}


void 
Player::HandleRectCollision(const Rectangle& rect) {
  // player & rect center point
  const Vector2 player_center {
    player_rect_.x + player_size_ / 2.f,
    player_rect_.y + player_size_ / 2.f,
  };
  const Vector2 rect_center {
    rect.x + config::kCellSize / 2.f,
    rect.y + config::kCellSize / 2.f,
  };

  // distance between the 2 centers
  const Vector2 center_delta = Vector2Subtract(player_center, rect_center);

  // half widths & heights
  const Vector2 player_halves {
    player_size_ / 2.f,
    player_size_ / 2.f,
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
    player_rect_.x += dist_x * (center_delta.x / fabsf(center_delta.x));
  }
  // collide from top or bottom
  else {
    player_rect_.y += dist_y * (center_delta.y / fabsf(center_delta.y));
    vertical_speed_ = 0.f;

    // if player is above the rect it's counted as grounded.
    if (player_center.y < rect_center.y) {
      is_grounded_ = true;
    }
  }
}
void
Player::HandleLandedRectCollision() {
  for (Rectangle rect : game_ref_.landed_block_rect) {
    if (CheckCollisionRecs(player_rect_, rect)) {
      HandleRectCollision(rect);
    }
  }
}
void
Player::HandleCurrentRectCollision() {
  for (Rectangle rect : game_ref_.current_block_rect) {
    if (CheckCollisionRecs(player_rect_, rect)) {
      HandleRectCollision(rect);
    }
  }
}

void
Player::HandleDeath() {
  for (Rectangle rect : game_ref_.current_block_rect) {
    if (CheckCollisionRecs(player_rect_, rect) && is_grounded_) {
      std::cout << "Game Over" << std::endl;
    }
  }
}
