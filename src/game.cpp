#include "game.hpp"
#include "config.hpp"
#include "position.hpp"
#include "tetromino.hpp"
#include <raylib.h>
#include <vector>
#include <cstdlib>

// TODO: Find a way to move the rect vector down/remove it with the colored grid.

Game::Game() 
    : grid {Grid()}
    , blocks {El(), Jay(), Straight(), Square(), Tee(), SkewS(), SkewZ()}
    , current_block(get_random_block())
    , next_block(get_random_block())
    , last_update_time {0.0}
    , player {*this}
  
{}

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
    player.render();
}

void
Game::update() {
    player.update();
    handle_input();

    if (event_triggered(0.5)) {
        block_move_down();
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
        block_move_left();
        break;
    case KEY_L:
        block_move_right();
        break;
    case KEY_K:
        block_move_down();
        break;
    case KEY_I:
        rotate_block();
        break;
    }

    player.handle_input();
}

void
Game::block_move_left() {
    current_block.move(0, -1);

    // if block out of bound to the left, move the block 1 cell to the right.
    if (is_block_outside() || is_grid_occupied() == false) {
        current_block.move(0, 1);
    }
}
void
Game::block_move_right() {
    current_block.move(0, 1);
    if (is_block_outside() || is_grid_occupied() == false) {
        current_block.move(0, -1);
    }
}
void
Game::block_move_down() {
    current_block.move(1, 0);
    if (is_block_outside() || is_grid_occupied() == false) {
        current_block.move(-1, 0);
        lock_block();
    }
}

void
Game::rotate_block() {
    current_block.rotate();
    if (is_block_outside() || is_grid_occupied() == false) {
        current_block.undo_rotate();
    }
}

bool
Game::is_grid_occupied() {
    std::vector<Position> current_checked_cell = current_block.get_cell_position();

    for (Position tile : current_checked_cell) {
        if (grid.is_grid_empty(tile.row, tile.col) == false) {
            return false;
        }
    }
    return true;
}

void
Game::lock_block() {
    std::vector<Position> current_checked_cell = current_block.get_cell_position();

    // Set the grid where the current block located to match the current block
    // color.
    // Also spawn Rectangle for the player to collide.
    for (Position tile : current_checked_cell) {
        grid.grid_cell[tile.row][tile.col] = current_block.color_id;
        grid_rect.push_back({
            (float)tile.col * config::cell_size + config::GridOffsetX, 
            (float)tile.row * config::cell_size + config::GridOffsetY, 
            config::cell_size, 
            config::cell_size
        });
    }

    // Update the block
    current_block = next_block;
    next_block = get_random_block();

    grid.clear_full_row();
}

bool
Game::is_block_outside() {
    std::vector<Position> current_checked_cell = current_block.get_cell_position();

    for (Position cell_pos : current_checked_cell) {
       if (grid.is_cell_outside(cell_pos.row, cell_pos.col)) {
          return true;
       }
    }

    return false;
}
