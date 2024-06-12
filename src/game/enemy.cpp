#include <iostream>
#include <raylib.h>
#include <raymath.h>

#include "enemy.hpp"
#include "game.hpp"
#include "config.hpp"

Enemy::Enemy(Game* game, int xPos) 
  : game_ {game}
  , collider_ (Rectangle {
      (float)xPos, 
      0.f, 
      Config::kCellSize / 2.f, 
      Config::kCellSize / 2.f
    })
  , renderer_ (collider_.collider())
  , transform_ (collider_.collider(), 75.f)
  , jump_cooldown (1.f)
  , current_jump_cooldonw_ (jump_cooldown)
  , is_alive_ {true}
  , marked_for_delete_ (false)
{
  collider_
    .addDownCollisionCallback([this](){
      this->transform_.is_grounded(true);
      this->transform_.vertical_speed(0.f);
    });
}
Enemy::~Enemy() {
  std::cout << "Enemy destroyed" << std::endl;
}

void
Enemy::render() {
  //DrawRectangleRec(*collider_.collider(), RED);
  renderer_.render(RED);
}

void 
Enemy::update() {
  transform_.handleGravity();
  collider_.handleCollsion(&Config::kRightWallRect);
  collider_.handleCollsion(&Config::kLeftWallRect);
  collider_.batchHandleCollision(&game_->current_block_rect);
  collider_.batchHandleCollision(&game_->landed_block_rect);
  moveToPlayer();

  // NOTE: Moved Jump() here to allow the enemy to jump on top of tetrominos.
  jump();
}

void
Enemy::moveToPlayer() {
  const float player_x = game_->player.rect().x;
  if ( player_x < collider_.collider()->x) {
    transform_.moveToDirection(-1.f);
  }
  else {
    transform_.moveToDirection(1.f);
  }
}

void 
Enemy::jump() {
  if (
      transform_.is_grounded()
      && is_alive_
      && current_jump_cooldonw_ <= 0
  ) {
    transform_.jump(-250.f);
    current_jump_cooldonw_ = jump_cooldown;
  }

  current_jump_cooldonw_ -= GetFrameTime();
}


// return ints for the score
int
Enemy::handleDeath() {
  // Preventing from enemy checking collision after death
  if (!is_alive_) {
    return 0;
  }

  for (const Rectangle& rect : game_->current_block_rect) {
    if (CheckCollisionRecs(*collider_.collider(), rect)) {
      std::cout << "enemy killed" << std::endl;
      is_alive_ = false;

      return 1;
    }
  }

  return 0;
}