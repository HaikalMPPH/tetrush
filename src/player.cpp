#include <cmath>
#include <iostream>
#include <raylib.h>
#include <raymath.h>

#include "player.hpp"
#include "config.hpp"
#include "game.hpp"


Player::Player(const Game* game)
  : collider_ (Rectangle {
      Config::kWinW/2.f, 
      Config::kWinH/2.f, 
      Config::kCellSize / 2.f, 
      Config::kCellSize / 2.f
    })
  , renderer_ (collider_.collider())
  , transform_ (collider_.collider(), 200.f)
  , is_alive_ {true}
  , game_ {game}
{
  collider_
    .addDownCollisionCallback([this](){
      this->transform_.is_grounded(true);
      this->transform_.vertical_speed(0.f);
    });
}
Rectangle
Player::rect() {
  return *collider_.collider();
}
void
Player::update() {
  // NOTE: Collision are handled after controls or the player won't jump.
  transform_.handleGravity();
  collider_.handleCollsion(&Config::kLeftWallRect);
  collider_.handleCollsion(&Config::kRightWallRect);
  collider_.batchHandleCollision(&game_->current_block_rect);
  collider_.batchHandleCollision(&game_->landed_block_rect);
}

void
Player::render() {
    renderer_.render(BLUE);
}

void 
Player::handleInput() {
  if (IsKeyDown(KEY_A)) {
    transform_.moveToDirection(-1);
  }
  if (IsKeyDown(KEY_D)) {
    transform_.moveToDirection(1);
  }
  if (IsKeyPressed(KEY_SPACE)) {
    transform_.jump(-300.f);
  }
}

// TODO: Rework this.
void
Player::handleDeath() {
  for (const Rectangle& rect : game_->current_block_rect) {
    if (CheckCollisionRecs(*collider_.collider(), rect)) {
      std::cout << "Game Over" << std::endl;
      is_alive_ = false;
    }
  }
}
