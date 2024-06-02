#include <ostream>
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

// TODO: Game over is now based on: - if player is below safe_y
//                                  - if player position is inside grid_rect

Game::Game() 
    : grid {Grid(*this)}
    , blocks {El(), Jay(), Straight(), Square(), Tee(), SkewS(), SkewZ()}
    , current_block {get_random_block()}
    , next_block {get_random_block()}
    , block_projection {current_block}
    , last_update_time {0.0}
    , player {*this}
    , min_safe_y {0.f}
{
    // 
    create_current_block_rect();

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
    debug_render_rect();
    // draw_projection();
}

void
Game::update() {
    player.update();
    handle_input();

    if (event_triggered(0.5)) {
        block_move_down(current_block);
        update_current_block_rect();
    }

    // DEBUG: testing safe y & danger x
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "Danger y:" << min_safe_y << " - " << max_safe_y << 
        " player y: " << player.player_rect.y << std::endl;

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
        update_current_block_rect();
        break;
    case KEY_L:
        block_move_right(current_block);
        block_move_right(block_projection);
        update_current_block_rect();
        break;
    case KEY_K:
        update_min_max_safe_y();
        block_instant_move_down(current_block);
        lock_block();
        break;
    case KEY_I:
        rotate_block(current_block);
        rotate_block(block_projection);
        update_current_block_rect();
        break;
    }

    player.handle_input();
}


void
Game::update_min_max_safe_y() {

    const std::vector<Position>& curr_block_pos = current_block.get_cell_position();
    const std::vector<Position>& proj_block_pos = block_projection.get_cell_position();
    // start from the bottom grid

    for (Position curr_pos : curr_block_pos) {
        float tmp_min = curr_pos.row * config::CellSize + config::GridOffsetY;
        if (tmp_min <= min_safe_y) {
            min_safe_y = tmp_min;
        }
    }
    for (Position proj_pos : proj_block_pos) {
        float tmp_max = proj_pos.row * config::CellSize + config::GridOffsetY + config::CellSize;
        if (tmp_max >= max_safe_y) {
            max_safe_y = tmp_max;
        }
    }
}


void
Game::block_move_left(Block& block) {
    block.move(0, -1);

    block_instant_move_down(block_projection);
    update_projection_pos();

    // if block out of bound to the left, move the block 1 cell to the right.
    if (is_block_outside(block) || is_grid_occupied(block) == false) {
        block.move(0, 1);
    }

}
void
Game::block_move_right(Block& block) {
    block.move(0, 1);

    block_instant_move_down(block_projection);
    update_projection_pos();

    if (is_block_outside(block) || is_grid_occupied(block) == false) {
        block.move(0, -1);
    }

}
void
Game::block_move_down(Block& block) {
    block.move(1, 0);

    block_instant_move_down(block_projection);
    update_projection_pos();

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


    block_instant_move_down(block_projection);
    update_projection_pos();

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
    update_min_max_safe_y();

    // Process player.handle_death().
    player.handle_death();

    std::vector<Position> current_checked_cell = current_block.get_cell_position();

    // Set the grid where the current block located to match the current block
    // color.
    // Also spawn Rectangle for the player to collide.
    for (Position tile : current_checked_cell) {
        grid.grid_cell[tile.row][tile.col] = current_block.color_id;

        // TODO: wrap this in a function similar to create_current_block_rect()
        landed_block_rect.push_back({
            (float)tile.col * config::CellSize + config::GridOffsetX, 
            (float)tile.row * config::CellSize + config::GridOffsetY, 
            config::CellSize, 
            config::CellSize
        });
    }

    // TODO: handle player/enemy deaths here
    //

    // Update the block
    current_block = next_block;

    update_current_block_rect();

    // Instantly move block projection to the ground when created.
    block_projection = current_block;
    block_projection.color_id = 8;
    block_instant_move_down(block_projection);

    // prepare for the next block.
    next_block = get_random_block();

    grid.clear_full_row();
}


void
Game::create_current_block_rect() {
    const std::vector<Position>& curr_block_pos = current_block.get_cell_position();
    for (Position pos : curr_block_pos) {
        current_block_rect.push_back(Rectangle {
            (float)pos.col * config::CellSize + config::GridOffsetX,
            (float)pos.row * config::CellSize + config::GridOffsetY,
            config::CellSize,
            config::CellSize,
        });
    }
}
void
Game::clear_current_block_rect() {
    current_block_rect.clear();
}
void
Game::update_current_block_rect() {
    clear_current_block_rect();
    create_current_block_rect();
}


void
Game::update_projection_pos() {
    while (is_grid_occupied(block_projection) == false) {
        block_projection.move(-1, 0);
    }
}

void
Game::debug_render_rect() {
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
