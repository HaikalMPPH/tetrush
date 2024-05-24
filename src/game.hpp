#ifndef GAME_HPP
#define GAME_HPP

#include "grid.hpp"
#include "block.hpp"
#include "player.hpp"
#include <raylib.h>

struct Game {
// = VARIABLES ===========================================================
    Grid grid;

    // list of the available tetraminos.
    std::vector<Block> blocks;
    Block current_block;
    Block next_block;

    double last_update_time;

    // Player
    Player player;

    // Vector of rect that the position is matched with the color grid.
    // The rect is used for the player collision
    std::vector<Rectangle> grid_rect;

// = METHODS =============================================================
    Game();
    Block get_random_block();
    std::vector<Block> create_tetraminos();

    void render();
    void update();
    // Trigger an event every certain tick (this is for moving the tetraminos down automatically).
    // tick_interval: how many seconds before the event is triggered.
    bool event_triggered(double tick_interval);

    void handle_input();

    void block_move_left();
    void block_move_right();
    void block_move_down();
    void rotate_block();

    // Check if the grid next to/below the block is occupied.
    bool is_grid_occupied();
    // Called when the block reaches the ground.
    void lock_block();


    bool is_block_outside();
};

#endif
