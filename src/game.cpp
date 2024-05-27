#include <raylib.h>
#include <vector>
#include <cstdlib>
#include <iostream>

#include "game.hpp"
#include "block.hpp"
#include "colors.hpp"
#include "config.hpp"
#include "position.hpp"
#include "tetromino.hpp"

Game::Game() 
    : grid {Grid(*this)}
    , blocks {El(), Jay(), Straight(), Square(), Tee(), SkewS(), SkewZ()}
    , current_block {get_random_block()}
    , next_block {get_random_block()}
    , block_projection {current_block}
    , last_update_time {0.0}
    , player {*this}
    , safe_block_y {0.f}
    , min_danger_x {config::WinW}   // make it very big
    , max_danger_x {0.f}            // make it very small
  
{
    // Move the first block projection down.
    block_projection.color_id = 8;
    block_instant_move_down(block_projection);
}

Block
Game::get_random_block() {
    if (blocks.empty()) {
        blocks = create_tetraminos();
    }
    // spawn random tetraminos
    int rand_index = rand() % blocks.size();
    Block random_block = blocks[rand_index];
    
    // remove block from the block vector after randomly picked.
    blocks.erase(blocks.begin() + rand_index); // pointer arithmatics.
    
    return random_block;
}

std::vector<Block>
Game::create_tetraminos() {
    return {El(), Jay(), Straight(), Square(), Tee(), SkewS(), SkewZ()};
}

void 
Game::render() {
    grid.draw();
    current_block.draw();
    block_projection.draw();
    player.render();
    // debug_render_rect();
    // draw_projection();
}

void
Game::update() {
    player.update();
    handle_input();

    if (event_triggered(0.5)) {
        block_move_down(current_block);
        update_max_safe_y();

        // DEBUG: testing max_safe_y
        std::cout << safe_block_y << ", " << player.player_rect.y << std::endl;
    }

}

bool
Game::event_triggered(double tick_interval) {
    double current_time = GetTime();

    // if the time passed the tick_interval
    if (current_time - last_update_time >= tick_interval) {
        last_update_time = current_time;
        return true;
    }

    return false;
}

void
Game::handle_input() {
    int key = GetKeyPressed();

    switch (key) {
    case KEY_J:
        block_move_left(current_block);
        block_move_left(block_projection);
        break;
    case KEY_L:
        block_move_right(current_block);
        block_move_right(block_projection);
        break;
    case KEY_K:
        block_instant_move_down(current_block);
        lock_block();
        break;
    case KEY_I:
        rotate_block(current_block);
        rotate_block(block_projection);
        break;
    }

    player.handle_input();
}

void
Game::update_max_safe_y() {
    const std::vector<Position>& block_pos = current_block.get_cell_position();
    // start from the bottom grid
    // float safe_block_y = grid.num_of_row * config::CellSize + config::GridOffsetY;

    for (Position pos : block_pos) {
        if (pos.row * config::CellSize + config::GridOffsetY >= safe_block_y) {
            safe_block_y = pos.row * config::CellSize + config::GridOffsetY;
        }
    }
}
void
Game::update_min_max_danger_x() {
    reset_danger_x();

    const std::vector<Position>& block_pos = current_block.get_cell_position();
    for (Position pos : block_pos) {
        float tmp_min = pos.col * config::CellSize + config::GridOffsetX;
        // the end of block x coordinate.
        float tmp_max = tmp_min + config::CellSize;

        if (tmp_min < min_danger_x)
            min_danger_x = tmp_min;
        if (tmp_max > max_danger_x)
            max_danger_x = tmp_max;
    }

    // DEBUG
    std::cout << "Danger x: " << min_danger_x << " - " << max_danger_x << std::endl;
}
void
Game::reset_danger_x() {
    max_danger_x = 0.f;             // make it very small
    min_danger_x = config::WinW;    // make it very big
}

void
Game::block_move_left(Block& block) {
    block.move(0, -1);

    block_instant_move_down(block_projection);
    update_projection_rect_pos();

    // if block out of bound to the left, move the block 1 cell to the right.
    if (is_block_outside(block) || is_grid_occupied(block) == false) {
        block.move(0, 1);
    }

    update_min_max_danger_x();
}
void
Game::block_move_right(Block& block) {
    block.move(0, 1);

    block_instant_move_down(block_projection);
    update_projection_rect_pos();

    if (is_block_outside(block) || is_grid_occupied(block) == false) {
        block.move(0, -1);
    }

    update_min_max_danger_x();
}
void
Game::block_move_down(Block& block) {
    block.move(1, 0);

    block_instant_move_down(block_projection);
    update_projection_rect_pos();

    if (is_block_outside(block) || is_grid_occupied(block) == false) {
        block.move(-1, 0);
        lock_block();
    }
}
void
Game::block_instant_move_down(Block& block) {
    while(true) {
        block.move(1, 0);
        if (is_block_outside(block) || is_grid_occupied(block) == false) {
            block.move(-1, 0);
            break;
        }
    }
}

void
Game::rotate_block(Block& block) {
    block.rotate();

    update_max_safe_y();

    block_instant_move_down(block_projection);
    update_projection_rect_pos();

    if (is_block_outside(block) || is_grid_occupied(block) == false) {
        block.undo_rotate();
    }
}

bool
Game::is_grid_occupied(Block& block) {
    std::vector<Position> current_checked_cell = block.get_cell_position();

    for (Position tile : current_checked_cell) {
        if (grid.is_grid_empty(tile.row, tile.col) == false) {
            return false;
        }
    }
    return true;
}

void
Game::lock_block() {
    update_max_safe_y();
    update_min_max_danger_x();

    std::vector<Position> current_checked_cell = current_block.get_cell_position();

    // Set the grid where the current block located to match the current block
    // color.
    // Also spawn Rectangle for the player to collide.
    for (Position tile : current_checked_cell) {
        grid.grid_cell[tile.row][tile.col] = current_block.color_id;
        grid_rect.push_back({
            (float)tile.col * config::CellSize + config::GridOffsetX, 
            (float)tile.row * config::CellSize + config::GridOffsetY, 
            config::CellSize, 
            config::CellSize
        });
    }
    // TODO: Process player.handle_death() here.


    // Update the block
    current_block = next_block;

    // Instantly move block projection to the ground when created.
    block_projection = current_block;
    block_projection.color_id = 8;
    block_instant_move_down(block_projection);

    // prepare for the next block.
    next_block = get_random_block();

    grid.clear_full_row();
    safe_block_y = 0.f;
    reset_danger_x();
}

void
Game::draw_projection() {
}
void
Game::create_projection_rect() {
}
void
Game::update_projection_rect_pos() {
    while (is_grid_occupied(block_projection) == false) {
        block_projection.move(-1, 0);
    }
}

void
Game::debug_render_rect() {
    // DEBUG: Render grid_rect
    for (Rectangle rect : grid_rect) {
        DrawRectangleRec(rect, PINK);
    }
}

bool
Game::is_block_outside(Block& block) {
    std::vector<Position> current_checked_cell = block.get_cell_position();

    for (Position cell_pos : current_checked_cell) {
       if (grid.is_cell_outside(cell_pos.row, cell_pos.col)) {
          return true;
       }
    }

    return false;
}
