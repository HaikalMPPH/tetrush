#include <iostream>
#include <raylib.h>
#include <raymath.h>

#include "enemy.hpp"
#include "game.hpp"
#include "config.hpp"

enemy::enemy(::game* game, int xPos) 
  : marked_for_delete (false)
  , game_ {game}
  , collider_ (Rectangle {
      (float)xPos, 
      0.f, 
      config::cell_size / 2.f, 
      config::cell_size / 2.f
    })
  , renderer_ (collider_.collider())
  , transform_ (collider_.collider(), 75.f)
  , subscriber_ {}
  , jump_cooldown (1.f)
  , current_jump_cooldonw_ (jump_cooldown)
  , is_alive_ {true}
{
  collider_
    .add_down_collision_callback([this](){
      this->transform_.is_grounded(true);
      this->transform_.vertical_speed(0.f);
    });

  subscriber_
    .add_notify_callback("OnBlockLock", [this](){
        //std::cout << "Enemy: On Block Lock" << std::endl;
        handle_death();
    })
    ->add_notify_callback("OnBlockMove", [this](){
        //std::cout << "Enemy: On Block Move Down" << std::endl;
        handle_death();
    });

  enemy_event_publisher_
    .add_subscriber(&game_->subscriber_)
    ->add_subscriber(game_->player.subscriber());
}
enemy::~enemy() {
  std::cout << "Enemy destroyed" << std::endl;
}
event_subscriber*
enemy::subscriber() {
  return &subscriber_;
}

void
enemy::render() {
  //DrawRectangleRec(*collider_.collider(), RED);
  renderer_.render(RED);
}

void 
enemy::update() {
  transform_.handle_gravity();
  collider_.handle_collision(&config::r_wall_rect);
  collider_.handle_collision(&config::l_wall_rect);
  if (is_alive_) {
    move_to_player();

    collider_.batch_handle_collision(&game_->current_block_rect);
    collider_.batch_handle_collision(&game_->landed_block_rect);
    collider_.handle_collision(&config::ground_rect);
    // NOTE: Moved Jump() here to allow the enemy to jump on top of tetrominos.
    jump();
  }

  if (transform_.rect()->y > config::win_h) {
    marked_for_delete = true;
  }
}

void
enemy::move_to_player() {
  const float player_x = game_->player.collider()->x;

  if (CheckCollisionRecs(*game_->player.collider(), *collider_.collider())) {
    enemy_event_publisher_.notify_subscriber("OnEnemyTouched");
  }

  if (player_x < collider_.collider()->x) {
    transform_.move_to_direction(-1.f);
  }
  else {
    transform_.move_to_direction(1.f);
  }
}

void 
enemy::jump() {
  if (
      transform_.is_grounded()
      && is_alive_
      && current_jump_cooldonw_ <= 0
  ) {
    PlaySound(config::enemy_jump_sound);
    transform_.jump(-250.f);
    current_jump_cooldonw_ = jump_cooldown;
  }

  current_jump_cooldonw_ -= GetFrameTime();
}

void
enemy::death() {
  std::cout << "enemy killed" << std::endl;
  is_alive_ = false;
  transform_.jump(-250.f);
  enemy_event_publisher_.notify_subscriber("OnEnemyDeath");
}

// return ints for the score
void
enemy::handle_death() {
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
