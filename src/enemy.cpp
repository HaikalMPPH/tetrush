#include <iostream>
#include <raylib.h>
#include <raymath.h>

#include "enemy.hpp"
#include "game.hpp"
#include "config.hpp"

// TODO: Fix enemy can't jump on top of tetrominos.

Enemy::Enemy(const Game& game) 
  : game_ref_ (game)
  , move_direction_ (0.f)
  , enemy_size_ (config::kCellSize / 2.f)
  , enemy_rect_ ({
      config::kWinW / 2.f, 
      config::kWinH / 2.f,
      enemy_size_,
      enemy_size_,
    })
  , enemy_gravity_ (config::kGameGravity)
  , jump_height_ (-200.f)
  , speed_ (75.f)
  , vertical_speed_ (0.f)
  , is_jumpable_ (false)
  , kJumpCooldown (1.f)
  , current_jump_cooldown_ (kJumpCooldown)
  , is_alive_ (true)
  , is_grounded_ (true)
{}

void
Enemy::Render() {
  DrawRectangleRec(enemy_rect_, RED);
}

void 
Enemy::Update() {
  HandleGravity();
  MoveToPlayer();
  Jump();

  HandleLandedRectCollision();
  HandleCurrentRectCollision();
}

void
Enemy::MoveToPlayer() {
  const float enemy_x = game_ref_.player.player_rect().x;
  if ( enemy_x < enemy_rect_.x) {
    move_direction_ = -1.f;
  }
  else {
    move_direction_ = 1.f;
  }

  enemy_rect_.x += move_direction_ * speed_ * GetFrameTime();
}

void
Enemy::HandleGravity() {
  vertical_speed_ += enemy_gravity_;
  enemy_rect_.y += vertical_speed_ * GetFrameTime();
  if (enemy_rect_.y + enemy_size_ >= game_ref_.ground_y) {
    is_grounded_ = true;
    is_jumpable_ = true;
    vertical_speed_ = 0.f;
    enemy_gravity_ = 0.f;
    enemy_rect_.y = game_ref_.ground_y - enemy_size_;

  }

  // return gravity to normal.
  else {
    enemy_gravity_ = config::kGameGravity;
  }
}
void 
Enemy::Jump() {
  if (
      is_grounded_
      && current_jump_cooldown_ <= 0
  ) {
    vertical_speed_ = jump_height_;
    is_grounded_ = false;
    current_jump_cooldown_ = kJumpCooldown;
  }

  current_jump_cooldown_ -= GetFrameTime();
}

void
Enemy::HandleRectCollision(const Rectangle& rect) {
  const Vector2 enemy_center {
    enemy_rect_.x + enemy_size_ / 2.f,
    enemy_rect_.y + enemy_size_ / 2.f,
  };
  const Vector2 rect_center {
    rect.x + config::kCellSize / 2.f,
    rect.y + config::kCellSize / 2.f,
  };

  const Vector2 center_delta = Vector2Subtract(enemy_center, rect_center);

  const Vector2 enemy_halves {
    enemy_size_ / 2.f,
    enemy_size_ / 2.f,
  };
  const Vector2 rect_halves {
    config::kCellSize / 2.f,
    config::kCellSize / 2.f,
  };

  const float dist_x = enemy_halves.x + rect_halves.x - fabsf(center_delta.x);
  const float dist_y = enemy_halves.y + rect_halves.y - fabsf(center_delta.y);

  if (dist_x < dist_y) {
    enemy_rect_.x += dist_x * (center_delta.x / fabsf(center_delta.x));
  }
  else {
    enemy_rect_.y += dist_y * (center_delta.y / fabsf(center_delta.y));
    vertical_speed_ = 0.f;

    if (enemy_center.y < rect_center.y) {
      is_grounded_ = true;
    }
  }
}
void
Enemy::HandleLandedRectCollision() {
  for (const Rectangle& rect : game_ref_.landed_block_rect) {
    if (CheckCollisionRecs(enemy_rect_, rect)) {
      HandleRectCollision(rect);
    }
  }
}
void
Enemy::HandleCurrentRectCollision() {
  for (const Rectangle& rect : game_ref_.current_block_rect) {
    if (CheckCollisionRecs(enemy_rect_, rect)) {
      HandleRectCollision(rect);
    }
  }
}
void
Enemy::HandleDeath() {
  for (const Rectangle& rect : game_ref_.current_block_rect) {
    if (CheckCollisionRecs(enemy_rect_, rect)) {
      std::cout << "enemy killed" << std::endl;
      is_alive_ = false;
    }
  }
}
