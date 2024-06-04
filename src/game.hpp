#ifndef GAME_HPP
#define GAME_HPP

#include <raylib.h>
#include <vector>

#include "position.hpp"
#include "grid.hpp"
#include "block.hpp"
#include "player.hpp"

// namespace tetrush {
    struct game_s {
    // = VARIABLES ===========================================================
        grid_s grid;

        // list of the available tetraminos.
        std::vector<block_c> blocks;
        block_c current_block;
        block_c next_block;

        // Tetramino projection.
        block_c block_projection;

        double last_update_time;

        // Player
        player_s player;

        // Vector of rect that the position is matched with the color grid.
        // The rect is used for the player collision
        std::vector<Rectangle> landed_block_rect;     // collider of a block that are on the ground.
        std::vector<Rectangle> current_block_rect;    // collider of the current falling block.

        // * The maximum height of the current_block. This allow the player to vault over the block if
        //   it's on the higher ground.
        // * Resets every lock_block() call.
        float min_safe_y, // the very top of the current block y.
            max_safe_y; // the very bottom of the projection block y.
        // float min_danger_x,
        //       max_danger_x;

    // = METHODS =============================================================
        game_s();
        block_c get_random_block();

        std::vector<block_c> create_tetrominos();

        void render();
        void update();
        // * Trigger an event every certain tick (this is for moving the tetraminos down automatically).
        // * tick_interval: how many seconds before the event is triggered.
        bool event_triggered(double tick_interval);

        void handle_input();


        // * Update the min and max x coordinate that will kill the player/enemy.
        // * Called every move_right or move_left and when spawning current_block. 
        void update_min_max_danger_x();
        void reset_danger_x();

        void block_move_left(block_c& block);
        void block_move_right(block_c& block);
        void block_move_down(block_c& block);
        void block_instant_move_down(block_c& block);
        void rotate_block(block_c& block);

        // Check if the grid next to/below the block is occupied.
        bool is_grid_occupied(block_c& block);

        // Called when the block reaches the ground.
        // Also processed if player/enemy is "squashable"
        void lock_block();
        void update_grid_color(std::vector<position_s> cell);
        void update_landed_block_rect(std::vector<position_s> cell);

        void create_current_block_rect();
        void clear_current_block_rect();
        void update_current_block_rect();   // empty and recreate current_block_rect

        //
        void update_projection();
        void update_projection_pos();

        // DEBUG: render tetromino collider.
        void debug_render_rect();


        bool is_block_outside(block_c& block);
    };


// }
#endif // GAME_HPP
