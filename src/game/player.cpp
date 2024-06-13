#include <iostream>
#include <raylib.h>
#include <raymath.h>

#include "player.hpp"
#include "config.hpp"
#include "game.hpp"


Player::Player(Game* game)
  : collider_ {Rectangle {
      config::kWinW/2.f, 
      config::kWinH/2.f, 
      config::kCellSize / 2.f, 
      config::kCellSize / 2.f
    }}
  , renderer_ {collider_.collider()}
  , transform_ {collider_.collider(), 200.f}
  , subscriber_ {}
  , player_event_publisher_ {}
  , is_alive_ {true}
  , game_ {game}
{
  collider_
    .addDownCollisionCallback([this](){
      transform_.is_grounded(true);
      transform_.vertical_speed(0.f);
    });

  subscriber_
    .addNotifyCallback("OnBlockLock", [this](){
      std::cout << "Player: On Block Lock" << std::endl;
      handleDeath();
    })
    ->addNotifyCallback("OnBlockMove", [this](){
      //std::cout << "Player: On Block Move Down" << std::endl;
      handleDeath();
    })
    ->addNotifyCallback("OnStackFull", [this](){
      transform_.jump(-300.f);
      is_alive_ = false;
    });

  player_event_publisher_.addSubscriber(&game->subscriber_);
}
Rectangle
Player::rect() {
  return *collider_.collider();
}
EventSubscriber*
Player::subscriber() {
  return &subscriber_;
}
void
Player::update() {
  transform_.handleGravity();
  collider_.handleCollision(&config::kLeftWallRect);
  collider_.handleCollision(&config::kRightWallRect);
  if (is_alive_) {
    collider_.batchHandleCollision(&game_->current_block_rect);
    collider_.batchHandleCollision(&game_->landed_block_rect);
    collider_.handleCollision(&config::kGroundRect);
    handleInput();
  }
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
      is_alive_ = false;

      // add little jump when death
      transform_.jump(-300.f);

      player_event_publisher_.notifySubscriber("OnPlayerDeath");
    }
  }
}
