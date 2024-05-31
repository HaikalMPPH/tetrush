#ifndef GAME_HPP
#define GAME_HPP

#include <raylib.h>

#include "grid.hpp"
#include "block.hpp"
#include "player.hpp"

struct Game {
// = VARIABLES ===========================================================
    Grid grid;

    // list of the available tetraminos.
    std::vector<Block> blocks;
    Block current_block;
    Block next_block;

    // Tetramino projection.
    Block block_projection;

    double last_update_time;

    // Player
    Player player;

    // Vector of rect that the position is matched with the color grid.
    // The rect is used for the player collision
    std::vector<Rectangle> grid_rect;

    // * The maximum height of the current_block. This allow the player to vault over the block if
    //   it's on the higher ground.
    // * Resets every lock_block() call.
    float min_safe_y, // the very top of the current block y.
          max_safe_y; // the very bottom of the projection block y.
    // float min_danger_x,
    //       max_danger_x;

// = METHODS =============================================================
    Game();
    Block get_random_block();

    std::vector<Block> create_tetraminos();

    void render();
    void update();
    // * Trigger an event every certain tick (this is for moving the tetraminos down automatically).
    // * tick_interval: how many seconds before the event is triggered.
    bool event_triggered(double tick_interval);

    void handle_input();

    // * Get the max y of the current_block to determine the safe height player can vault over the
    //   block.
    // * This method is called every:
    //   - block rotaion
    //   - event triggered
    //   - early in lock_block() call.
    void update_min_max_safe_y();
    // * reset to a very big number.
    void reset_safe_y();

    // * Update the min and max x coordinate that will kill the player/enemy.
    // * Called every move_right or move_left and when spawning current_block. 
    void update_min_max_danger_x();
    void reset_danger_x();

    void block_move_left(Block& block);
    void block_move_right(Block& block);
    void block_move_down(Block& block);
    void block_instant_move_down(Block& block);

    void rotate_block(Block& block);

    // Check if the grid next to/below the block is occupied.
    bool is_grid_occupied(Block& block);
    // Called when the block reaches the ground.
    // Also processed if player/enemy is "squashable"
    void lock_block();

    //
    void update_projection_pos();

    // DEBUG: render tetromino collider.
    void debug_render_rect();


    bool is_block_outside(Block& block);
};

#endif // GAME_HPP
