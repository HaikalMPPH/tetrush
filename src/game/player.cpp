#include <iostream>
#include <raylib.h>
#include <raymath.h>

#include "player.hpp"
#include "config.hpp"
#include "game.hpp"


player::player(::game* game)
  : collider_ {::Rectangle {
      //config::kWinW/2.f, 
      //config::kWinH/2.f, 
      -10, -10,
      config::cell_size / 2.f, 
      config::cell_size / 2.f
    }}
  , renderer_ {collider_.collider()}
  , transform_ {collider_.collider(), 200.f}
  , subscriber_ {}
  , player_event_publisher_ {}
  , is_alive_ {true}
  , game_ {game}
  //, jump_sound_ {LoadSound("res/audio/jump.wav")}
{
  collider_
    .add_down_collision_callback([this](){
      transform_.is_grounded(true);
      transform_.vertical_speed(0.f);
    });

  subscriber_
    .add_notify_callback("OnBlockLock", [this](){
      std::cout << "Player: On Block Lock" << std::endl;
      handle_death();
    })
    ->add_notify_callback("OnBlockMove", [this](){
      //std::cout << "Player: On Block Move Down" << std::endl;
      handle_death();
    })
    ->add_notify_callback("OnStackFull", [this](){
      death();
    })
    ->add_notify_callback("OnEnemyTouched", [this](){
      death();
    })
    ->add_notify_callback("OnGameRestart", [this](){
      collider_.collider()->x = config::win_w/2.f;
      collider_.collider()->y = config::win_h/2.f;
      transform_.vertical_speed(0.f);
      is_alive_ = true;
    });

  player_event_publisher_.add_subscriber(&game->subscriber_);
}
player::~player() {
  //UnloadSound(jump_sound_);
}

::Rectangle*
player::collider() {
  return collider_.collider();
}
::event_subscriber*
player::subscriber() {
  return &subscriber_;
}
void
player::update() {
  transform_.handle_gravity();
  collider_.handle_collision(&config::l_wall_rect);
  collider_.handle_collision(&config::r_wall_rect);
  if (is_alive_) {
    collider_.batch_handle_collision(&game_->current_block_rect);
    collider_.batch_handle_collision(&game_->landed_block_rect);
    collider_.handle_collision(&config::ground_rect);
    handle_input();
  }
}

void
player::render() {
    renderer_.render(BLUE);
}

void 
player::handle_input() {
  if (IsKeyDown(KEY_A)) {
    transform_.move_to_direction(-1);
  }
  if (IsKeyDown(KEY_D)) {
    transform_.move_to_direction(1);
  }
  if (IsKeyPressed(KEY_SPACE)) {
    if (transform_.is_grounded()) {
      PlaySound(config::player_jump_sound);
    }
    transform_.jump(-300.f);
  }
}

void
player::death() {
  is_alive_ = false;
  PlaySound(config::game_over_sound);

  // add little jump when death
  transform_.jump(-300.f);

  player_event_publisher_.notify_subscriber("OnPlayerDeath");
}

// TODO: Rework this.
void
player::handle_death() {
  for (const Rectangle& rect : game_->current_block_rect) {
    if (CheckCollisionRecs(*collider_.collider(), rect)) {
      death();
    }
  }
}
