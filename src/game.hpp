#ifndef GAME_HPP
#define GAME_HPP

#include "grid.hpp"
#include "block.hpp"

struct Game {
// = VARIABLES ===========================================================
    Grid grid;

    // list of the available tetraminos.
    std::vector<Block> blocks;
    Block current_block;
    Block next_block;

    double last_update_time;

// = METHODS =============================================================
    Game();
    Block get_random_block();
    std::vector<Block> create_tetraminos();

    void draw();
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
