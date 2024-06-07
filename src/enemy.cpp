#include <iostream>
#include <raylib.h>

#include "enemy.hpp"
#include "game.hpp"
#include "config.hpp"

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
  , speed_ (75.f)
  , vertical_speed_ (0.f)
{}

void
Enemy::Render() {
  DrawRectangleRec(enemy_rect_, RED);
}

void 
Enemy::Update() {
  HandleGravity();
  MoveToPlayer();
}

void
Enemy::MoveToPlayer() {
  float player_x = game_ref_.player.player_rect().x;
  if ( player_x < enemy_rect_.x) {
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
    //is_grounded_ = true;
    vertical_speed_ = 0.f;
    enemy_gravity_ = 0.f;
    enemy_rect_.y = game_ref_.ground_y - enemy_size_;

  }

  // return gravity to normal.
  else {
    enemy_gravity_ = config::kGameGravity;
  }
}
