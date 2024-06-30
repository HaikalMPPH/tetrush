#include <algorithm>
#include <raylib.h>
#include <vector>
#include <iostream>

#include "game.hpp"
#include "block.hpp"
#include "config.hpp"
#include "enemy.hpp"
#include "position.hpp"
#include "tetromino.hpp"
#include "colors.hpp"

game::game() 
{
  create_current_block_rect();
  update_projection();

  subscriber_
    .add_notify_callback("OnEnemyDeath", [this](){
      PlaySound(config::enemy_killed_sound);
      score += 2;

      for (::enemy* enemy : enemies) {
        if (enemy->marked_for_delete) {
          game_event_publisher_.remove_subscriber(enemy->subscriber());
          enemies.erase(
            std::remove(
                enemies.begin(),
                enemies.end(),
                enemy
            ),
            enemies.end()
          );
          delete enemy;
        }
      }
    })
    ->add_notify_callback("OnPlayerDeath", [this](){
      handle_game_over();
    });

  // NOTE: enemy subscriber are assigned on the spawner function.
  game_event_publisher_
    .add_subscriber(player.subscriber());
}
game::~game() {
  for (::enemy* enemy : enemies) {
    delete enemy;
  }
}

::block
game::pick_random_block() {
  if (block.empty()) {
    block = create_tetrominos();
  }

  // spawn random tetraminos from the list of tetrominos in game_s::blocks vector.
  const int rand_index = rand() % block.size();
  ::block rand_block = block[rand_index];
  
  // remove block from the block vector after randomly picked.
  block.erase(block.begin() + rand_index); // pointer arithmatics.
  
  return rand_block;
}

vector<::block>
game::create_tetrominos() {
  return {::el(), ::jay(), ::straight(), ::square(), ::tee(), ::skew_s(), ::skew_z()};
}

::enemy*
game::create_enemy() {
  const int maxX = config::n_cols * config::cell_size;
  const int randX = (rand() % maxX) + config::grid_off_x;

  // DEBUG:
  std::cout << "::Enemy spawned!" << std::endl; 

  ::enemy* new_enemy = new ::enemy(this, randX);
  game_event_publisher_.add_subscriber(new_enemy->subscriber());

  return new_enemy;
}
void
game::append_enemy() {
  if (current_enemy_spawn_cooldown >= enemy_spawn_cooldown) {
    enemies.push_back(create_enemy());
    current_enemy_spawn_cooldown = 0.f;
  }

  current_enemy_spawn_cooldown += GetFrameTime();
}

void 
game::render() {
  grid.draw();

  if (!is_game_started) {
    DrawText(
      "PRESS [ESC] TO EXIT", 
      config::win_w * 3/5, config::grid_off_y + 10, 
      30, 
      colors::grey
    );
  }
  if (screen_state_ == screen_state::main_game) {
    if (!is_game_started && !is_game_over) {
      DrawText(
        "TETRUSH", 
        config::win_w * 3 / 8 - 175 , config::win_h / 2 - 200, 
        150, 
        colors::grey
      );
    }
    if (!is_game_started) {
      DrawText(
        "PRESS [SPACE] TO START", 
        config::win_w / 4 , config::win_h / 2 + 75, 
        60, 
        colors::grey
      );

      DrawText(
        "PRESS [/] FOR HELP", 
        config::grid_off_x + 10 , config::grid_off_y + 10, 
        30, 
        colors::grey
      );
    }
    
    // score
    if (is_game_over || is_game_started) {
      DrawText(
        std::to_string(score).c_str(), 
        config::win_w / 2, config::win_h / 2, 
        75, 
        colors::grey
      );
    }
      

    if (!is_game_over && is_game_started) {
      current_block.draw();
      block_projection.draw();
      for (::enemy* enemy : enemies) {
        enemy->render();
      }
    }
    else if (is_game_over && !is_game_started) {
      DrawText(
        "GAME OVER", 
        config::win_w * 3 / 8 , config::win_h / 2 - 75, 
        75, 
        colors::grey
      );
    }

    player.render();
  }

  if (screen_state_ == screen_state::help_menu) {
    DrawText(
      "PRESS [/] AGAIN TO GO BACK", 
      config::grid_off_x + 10 , config::grid_off_y + 10, 
      30, 
      colors::grey
    );
    DrawText(
      help_menu_str, 
      config::grid_off_x + 10 , config::grid_off_y + 75, 
      50, 
      colors::grey
    );
  }

  //debugRenderRect();

  // DEBUG
  //DrawRectangleRec(config::kLeftWallRect, BLUE);
  //DrawRectangleRec(config::kRightWallRect, BLUE);
  //DrawRectangleRec(config::kGroundRect, BLUE);
}

void
game::update() {
  player.update();
  handle_input();

  if (
    !is_game_over 
    && is_game_started
    && screen_state_ == screen_state::main_game
  ) {
    UpdateMusicStream(config::game_music);
    // Restart music after done playing
    if (
      GetMusicTimePlayed(config::game_music)/GetMusicTimeLength(config::game_music) > 1.0f
    ) {
      StopMusicStream(config::game_music);
      PlayMusicStream(config::game_music);
    }

    append_enemy();

    for (::enemy* enemy : enemies) {
      enemy->update();
    }

    if (event_triggered(0.5)) {
      block_move_down(current_block);
      update_current_block_rect();
    }
  }
}

bool
game::event_triggered(double tickInterval) {
  double currentTime = GetTime();

  // if the time passed the tick_interval
  if (currentTime - last_update_time >= tickInterval) {
    last_update_time = currentTime;
    return true;
  }

  return false;
}

void
game::handle_input() {
  int key = GetKeyPressed();

  switch (key) {
    case KEY_J:
      if (is_game_started) {
        block_move_left(current_block);
        update_current_block_rect();
        update_projection();
      }
      break;
    case KEY_L:
      if (is_game_started) {
        block_move_right(current_block);
        update_current_block_rect();
        update_projection();
      }
      break;
    case KEY_K:
      if (is_game_started) {
        current_block_instant_move_down();
        lock_block();
      }
      break;
    case KEY_I:
      if (is_game_started) {
        rotate_block(current_block);
        update_current_block_rect();
        update_projection();
      }
      break;
    case KEY_SPACE:
      if (
        is_game_started == false
        && screen_state_ == screen_state::main_game
      ) {
        StopMusicStream(config::game_music);
        PlayMusicStream(config::game_music);
        on_game_restart();
      }
      break;
    case KEY_SLASH:
      if (
        screen_state_ == screen_state::main_game
        && !is_game_started
      ) {
        screen_state_ = screen_state::help_menu;
      }
      else if (screen_state_ == screen_state::help_menu) {
        screen_state_ = screen_state::main_game;
      }
  }
}



void
game::block_move_left(::block& block) {
  block.move(0, -1);

  if (!is_block_outside(current_block)) {
    game_event_publisher_.notify_subscriber("OnBlockMove");
  }

  // if block out of bound to the left, Move the block 1 cell to the right.
  if (is_block_outside(block) || is_grid_occupied(block) == false) {
    block.move(0, 1);
  }
}
void
game::block_move_right(::block& block) {
  block.move(0, 1);

  if (!is_block_outside(current_block)) {
    game_event_publisher_.notify_subscriber("OnBlockMove");
  }

  if (is_block_outside(block) || is_grid_occupied(block) == false) {
    block.move(0, -1);
  }
}
void
game::block_move_down(::block& block) {
  block.move(1, 0);

  if (!is_block_outside(current_block)) {
    game_event_publisher_.notify_subscriber("OnBlockMove");
  }

  if (is_block_outside(block) || is_grid_occupied(block) == false) {
    block.move(-1, 0);
    lock_block();
  }
}
void
game::blockw_instant_move_down(::block& block) {
  while(true) {
    block.move(1, 0);

    if (is_block_outside(block) || is_grid_occupied(block) == false) {
      block.move(-1, 0);
      break;
    }
  }
}
void
game::current_block_instant_move_down() {
  while(true) {
    current_block.move(1, 0);


    if (is_block_outside(current_block) || is_grid_occupied(current_block) == false) {
      current_block.move(-1, 0);
      break;
    }

    update_current_block_rect();

    if (!is_block_outside(current_block)) {
      game_event_publisher_.notify_subscriber("OnBlockMove");
    }
  }
}



void
game::rotate_block(::block& block) {
  block.rotate();

  if (!is_block_outside(current_block)) {
    game_event_publisher_.notify_subscriber("OnBlockMove");
  }

  if (is_block_outside(block) || is_grid_occupied(block) == false) {
    block.undo_rotate();
  }
}

bool
game::is_grid_occupied(::block& block) {
  vector<position> current_checked_cell = block.get_cell_position();

  for (position tile : current_checked_cell) {
    if (grid.is_grid_empty(tile.row, tile.col) == false) {
      return false;
    }
  }

  return true;
}
bool
game::is_block_outside(::block& block) {
  vector<position> current_checked_cell = block.get_cell_position();

  for (position cell_pos : current_checked_cell) {
    if (grid.is_cell_outside(cell_pos.row, cell_pos.col)) {
      return true;
    }
  }

  return false;
}
void
game::lock_block() {
  // DEBUG
  game_event_publisher_.notify_subscriber("OnBlockLock");

  vector<position> current_checked_cell = current_block.get_cell_position();

  // Set the grid where the current block located to match the current block
  // color.
  // Also spawn Rectangle for the player to collide.
  check_if_stack_full(&current_checked_cell);
  update_grid_color(&current_checked_cell);
  update_landed_block_rect(&current_checked_cell);

  // Update the block
  current_block = next_block;

  update_current_block_rect();

  // Instantly Move block projection to the ground when created.
  update_projection();

  // prepare for the next block.
  next_block = pick_random_block();

  score += (int)(grid.clear_full_row() * config::n_cols / 2.f);

  PlaySound(config::block_lock_sound);
}
void
game::update_grid_color(vector<position>* cell) {
  for (position pos : *cell) {
    grid.update_grid_color(pos.row, pos.col, current_block.color_id());
  }
}
void
game::update_landed_block_rect(vector<position>* cell) {
  for (position pos : *cell) {
    landed_block_rect.push_back({
      (float)pos.col * config::cell_size + config::grid_off_x, 
      (float)pos.row * config::cell_size + config::grid_off_y, 
      config::cell_size, 
      config::cell_size
    });
  }
}
void
game::check_if_stack_full(vector<position>* cell) {
  for (position pos : *cell) {
    if (pos.row <= 0) {
      std::cout << "Stack is full" << std::endl;
      game_event_publisher_.notify_subscriber("OnStackFull");
      handle_game_over();
      return;
    }
  }
}

void
game::create_current_block_rect() {
  const vector<position>& curr_block_pos = current_block.get_cell_position();
  for (position pos : curr_block_pos) {
    current_block_rect.push_back(Rectangle {
      (float)pos.col * config::cell_size + config::grid_off_x,
      (float)pos.row * config::cell_size + config::grid_off_y,
      config::cell_size,
      config::cell_size,
    });
  }
}
void
game::clear_current_block_rect() {
  current_block_rect.clear();
}
void
game::update_current_block_rect() {
  clear_current_block_rect();
  create_current_block_rect();
}

void
game::update_projection() {
  block_projection = current_block;
  block_projection.color_id(8);
  blockw_instant_move_down(block_projection);
}

void
game::debug_render_rect() {
  // DEBUG: 
  // Render landed_block_rect
  for (Rectangle rect : landed_block_rect) {
    DrawRectangleRec(rect, PINK);
  }
  // Render current_block_rect
  for (Rectangle rect : current_block_rect) {
    DrawRectangleRec(rect, SKYBLUE);
  }
}

void
game::handle_game_over() {
  current_block.color_id(0); // temporary fix to make the current block invisible.
  is_game_over = true;
  is_game_started = false;

  // restart enemy spawn cooldown
  current_enemy_spawn_cooldown = 0;

  grid.reset_color();

  StopMusicStream(config::game_music);
}

void
game::on_game_restart() {
  score = 0;

  current_block = next_block;
  next_block = pick_random_block();
  create_current_block_rect();
  update_projection();

  for (::enemy* enemy : enemies) {
    game_event_publisher_.remove_subscriber(enemy->subscriber());
    delete enemy;
  }
  enemies.clear();

  is_game_over = false;
  is_game_started = true;

  current_block_rect.clear();
  landed_block_rect.clear();

  game_event_publisher_.notify_subscriber("OnGameRestart");
}
