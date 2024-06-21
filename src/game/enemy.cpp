#include <iostream>
#include <raylib.h>
#include <raymath.h>

#include "enemy.hpp"
#include "game.hpp"
#include "config.hpp"

Enemy::Enemy(Game* game, int xPos) 
  : marked_for_delete (false)
  , game_ {game}
  , collider_ (Rectangle {
      (float)xPos, 
      0.f, 
      config::kCellSize / 2.f, 
      config::kCellSize / 2.f
    })
  , renderer_ (collider_.collider())
  , transform_ (collider_.collider(), 75.f)
  , subscriber_ {}
  , jump_cooldown (1.f)
  , current_jump_cooldonw_ (jump_cooldown)
  , is_alive_ {true}
{
  collider_
    .addDownCollisionCallback([this](){
      this->transform_.is_grounded(true);
      this->transform_.vertical_speed(0.f);
    });

  subscriber_
    .addNotifyCallback("OnBlockLock", [this](){
        //std::cout << "Enemy: On Block Lock" << std::endl;
        handleDeath();
    })
    ->addNotifyCallback("OnBlockMove", [this](){
        //std::cout << "Enemy: On Block Move Down" << std::endl;
        handleDeath();
    });

  enemy_event_publisher_
    .addSubscriber(&game_->subscriber_)
    ->addSubscriber(game_->player.subscriber());
}
Enemy::~Enemy() {
  std::cout << "Enemy destroyed" << std::endl;
}
EventSubscriber*
Enemy::subscriber() {
  return &subscriber_;
}

void
Enemy::render() {
  //DrawRectangleRec(*collider_.collider(), RED);
  renderer_.render(RED);
}

void 
Enemy::update() {
  transform_.handleGravity();
  collider_.handleCollision(&config::kRightWallRect);
  collider_.handleCollision(&config::kLeftWallRect);
  if (is_alive_) {
    moveToPlayer();

    collider_.batchHandleCollision(&game_->current_block_rect);
    collider_.batchHandleCollision(&game_->landed_block_rect);
    collider_.handleCollision(&config::kGroundRect);
    // NOTE: Moved Jump() here to allow the enemy to jump on top of tetrominos.
    jump();
  }

  if (transform_.rect()->y > config::kWinH) {
    marked_for_delete = true;
  }
}

void
Enemy::moveToPlayer() {
  const float player_x = game_->player.collider()->x;

  if (CheckCollisionRecs(*game_->player.collider(), *collider_.collider())) {
    enemy_event_publisher_.notifySubscriber("OnEnemyTouched");
  }

  if (player_x < collider_.collider()->x) {
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

void
Enemy::death() {
  std::cout << "enemy killed" << std::endl;
  is_alive_ = false;
  transform_.jump(-250.f);
  enemy_event_publisher_.notifySubscriber("OnEnemyDeath");
}

// return ints for the score
void
Enemy::handleDeath() {
  // Preventing from enemy checking collision after death
  if (!is_alive_) {
    return;
  }

  for (const Rectangle& rect : game_->current_block_rect) {
    if (CheckCollisionRecs(*collider_.collider(), rect)) {
      death();
      return;
    }
  }
}
