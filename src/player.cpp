#include <cmath>
#include <iostream>
#include <raylib.h>
#include <raymath.h>

#include "player.hpp"
#include "config.hpp"
#include "game.hpp"


Player::Player(const Game& game)
  : speed {200.f}
  , vertical_speed {0.f}
  , jump_height {-300.f}
  , player_size {config::kCellSize / 2.f}
  , player_rect {config::kWinW/2.f, 
                 config::kWinH/2.f, 
                 player_size, 
                 player_size}
  , move_direction_x {0.f}
  , player_gravity {20.f}
  , is_grounded {false}

  // Note: hardcoded num of rows. be careful when changing it in grid.cpp
  , game {game}
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
    DrawRectangleRec(player_rect, RED);
}

void 
Player::HandleInput() {
  if (IsKeyDown(KEY_A)) {
    move_direction_x = -1;
  }
  if (IsKeyDown(KEY_D)) {
    move_direction_x = 1;
  }
  if (IsKeyPressed(KEY_SPACE)) {
    Jump();
  }
}

void
Player::MoveToDirection() {
  player_rect.x += move_direction_x * speed * GetFrameTime();

  // reset to default after moving.
  move_direction_x = 0.f;
}

void
Player::HandleGravity() {
  vertical_speed += player_gravity;
  player_rect.y += vertical_speed * GetFrameTime();

  if (player_rect.y + player_size >= game.ground_y) {
    is_grounded = true;
    vertical_speed = 0.f;
    player_gravity = 0.f;
    player_rect.y = game.ground_y - player_size;

  }

  // return gravity to normal.
  else {
    player_gravity = 10.f;
  }
}

void
Player::HandleWallCollision() {
  const float left_wall_x = config::kGridOffsetX;
  const float right_wall_x = left_wall_x + config::kCellSize * config::kNumOfCols;

  // Collision with left wall.
  if (player_rect.x <= left_wall_x) {
      player_rect.x = left_wall_x;
  }

  // Collision with right wall.
  else if (player_rect.x + player_size >= right_wall_x) {
      player_rect.x = right_wall_x - player_size;
  }
}

void
Player::Jump() {
    if (is_grounded) {
        vertical_speed = jump_height;
        is_grounded = false;
    }
}


void 
Player::HandleRectCollision(const Rectangle& rect) {
  // player & rect center point
  const Vector2 player_center {
    player_rect.x + player_size / 2.f,
    player_rect.y + player_size / 2.f,
  };
  const Vector2 rect_center {
    rect.x + config::kCellSize / 2.f,
    rect.y + config::kCellSize / 2.f,
  };

  // distance between the 2 centers
  const Vector2 center_delta = Vector2Subtract(player_center, rect_center);

  // half widths & heights
  const Vector2 player_halves {
    player_size / 2.f,
    player_size / 2.f,
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
    player_rect.x += dist_x * (center_delta.x / fabsf(center_delta.x));
  }
  // collide from top or bottom
  else {
    player_rect.y += dist_y * (center_delta.y / fabsf(center_delta.y));
    vertical_speed = 0.f;

    // if player is above the rect it's counted as grounded.
    if (player_center.y < rect_center.y) {
      is_grounded = true;
    }
  }
}
void
Player::HandleLandedRectCollision() {
  for (Rectangle rect : game.landed_block_rect) {
    if (CheckCollisionRecs(player_rect, rect)) {
      HandleRectCollision(rect);
    }
  }
}
void
Player::HandleCurrentRectCollision() {
  for (Rectangle rect : game.current_block_rect) {
    if (CheckCollisionRecs(player_rect, rect)) {
      HandleRectCollision(rect);
    }
  }
}

void
Player::HandleDeath() {
  for (Rectangle rect : game.current_block_rect) {
    if (CheckCollisionRecs(player_rect, rect)) {
      std::cout << "Game Over" << std::endl;
    }
  }
}
