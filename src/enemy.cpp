#include "enemy.hpp"
#include "config.hpp"
#include <raylib.h>

Enemy::Enemy(const Game& game) 
  : game_ref_ (game)
  , move_direction_ (0.f)
  , enemy_rect_ ({
      config::kWinW / 2.f, 
      config::kWinH / 2.f,
      config::kCellSize / 2.f,
      config::kCellSize / 2.f,
    })
{}

void
Enemy::Render() {
  DrawRectangleRec(enemy_rect_, RED);
}

void
Enemy::MoveToDirection() {}

void
Enemy::HandleGravity() {
}
