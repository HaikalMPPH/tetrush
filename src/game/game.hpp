#ifndef GAME_HPP
#define GAME_HPP

#include <raylib.h>

#include "enemy.hpp"
#include "position.hpp"
#include "grid.hpp"
#include "block.hpp"
#include "player.hpp"

enum class screen_state {
  main_game,
  help_menu,
};

class game {
public:
  ::grid grid { this };

  ::screen_state screen_state_ { screen_state::main_game };
  bool on_help_menu { false };
  const char* help_menu_str {
    "PLAYER:\n\n\n"
    "\tA: Move Left\n\n\n"
    "\tD: Move Right\n\n\n"
    "\tSPACE: Jump\n\n\n"
    "\n\n\n"
    "TETROMINOS:\n\n\n"
    "\tJ: Move Block Left\n\n\n"
    "\tL: Move Block Right\n\n\n"
    "\tK: Lock Block to Ground\n\n\n"
    "\tI: Rotate Block"
  };

  int score { 0 };
  bool is_game_over { false };
  bool is_game_started { false };

  // list of the available tetraminos.
  std::vector<::block> block { create_tetrominos() };
  ::block current_block { pick_random_block() };
  ::block next_block { pick_random_block() };

  // Tetramino projection.
  ::block block_projection { current_block };

  double last_update_time { 0.0 };
  const float enemy_spawn_cooldown { 10.f };
  float current_enemy_spawn_cooldown { 0.f };

  ::player player { this };

  // ::Enemy are created on the fly
  std::vector<::enemy*> enemies {};

  // Vector of rect that the position is matched with the color grid.
  // The rect is used for the player collision
  std::vector<::Rectangle> landed_block_rect {};  // collider of a block that are on the ground.
  std::vector<::Rectangle> current_block_rect {}; // collider of the current falling block.
  ::event_publisher game_event_publisher_ {};
  ::event_subscriber subscriber_ {};

public:
  game();
  ~game();

public:
  ::block pick_random_block();

  std::vector<::block> create_tetrominos();
  ::enemy* create_enemy();
  void append_enemy();

  void render();
  void update();
  // * Trigger an event every certain tick (this is for moving the tetraminos down automatically).
  // * tick_interval: how many seconds before the event is triggered.
  bool event_triggered(double tickInterval);

  void handle_input();


  void block_move_left(::block& block);
  void block_move_right(::block& block);
  void block_move_down(::block& block);
  void blockw_instant_move_down(::block& block);
  void current_block_instant_move_down();
  void rotate_block(::block& block);

  // Check if the grid next to/below the block is occupied.
  bool is_grid_occupied(::block& block);
  bool is_block_outside(::block& block);

  void lock_block();
  void update_grid_color(std::vector<position>* cell);
  void update_landed_block_rect(std::vector<position>* cell);
  void check_if_stack_full(std::vector<position>* cell);

  void create_current_block_rect();
  void clear_current_block_rect();
  void update_current_block_rect();   // empty and recreate current_block_rect

  void update_projection();

  // DEBUG: render tetromino collider.
  void debug_render_rect();
  
  void handle_game_over();
  void on_game_restart();
};

#endif // GAME_HPP
