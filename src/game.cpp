#include <ostream>
#include <raylib.h>
#include <vector>
#include <cstdlib>
#include <iostream>

#include "game.hpp"
#include "block.hpp"
#include "config.hpp"
#include "position.hpp"
#include "tetromino.hpp"

// TODO: Game over is now based on: - if player is below safe_y
//                                  - if player position is inside grid_rect

game_s::game_s() 
    : grid {grid_s(*this)}
    , blocks {el_c(), jay_c(), straight_c(), square_c(), tee_c(), skews_c(), skewz_c()}
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
}

block_c
game_s::get_random_block() {
    if (blocks.empty()) {
        blocks = create_tetrominos();
    }
    // spawn random tetraminos
    const int rand_index = rand() % blocks.size();
    block_c random_block = blocks[rand_index];
    
    // remove block from the block vector after randomly picked.
    blocks.erase(blocks.begin() + rand_index); // pointer arithmatics.
    
    return random_block;
}

std::vector<block_c>
game_s::create_tetrominos() {
    return {el_c(), jay_c(), straight_c(), square_c(), tee_c(), skews_c(), skewz_c()};
}

void 
game_s::render() {
    grid.draw();
    current_block.draw();
    block_projection.draw();
    player.render();
    //debug_render_rect();
}

void
game_s::update() {
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
game_s::event_triggered(double tick_interval) {
    double current_time = GetTime();

    // if the time passed the tick_interval
    if (current_time - last_update_time >= tick_interval) {
        last_update_time = current_time;
        return true;
    }

    return false;
}

void
game_s::handle_input() {
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
game_s::block_move_left(block_c& block) {
    block.move(0, -1);

    // if block out of bound to the left, move the block 1 cell to the right.
    if (is_block_outside(block) || is_grid_occupied(block) == false) {
        block.move(0, 1);
    }

    update_projection();
    update_projection_pos();

}
void
game_s::block_move_right(block_c& block) {
    block.move(0, 1);

    if (is_block_outside(block) || is_grid_occupied(block) == false) {
        block.move(0, -1);
    }

    update_projection();
    update_projection_pos();

}
void
game_s::block_move_down(block_c& block) {
    block.move(1, 0);

    if (is_block_outside(block) || is_grid_occupied(block) == false) {
        block.move(-1, 0);
        lock_block();
    }

    update_projection();
    update_projection_pos();
}
void
game_s::block_instant_move_down(block_c& block) {
    while(true) {
        block.move(1, 0);

        if (is_block_outside(block) || is_grid_occupied(block) == false) {
            block.move(-1, 0);
            break;
        }
    }
}

void
game_s::rotate_block(block_c& block) {
    block.rotate();

    if (is_block_outside(block) || is_grid_occupied(block) == false) {
        block.undo_rotate();
    }

    update_projection();
    update_projection_pos();
}

bool
game_s::is_grid_occupied(block_c& block) {
    std::vector<position_s> currentCheckedCell = block.get_cell_position();

    for (position_s tile : currentCheckedCell) {
        if (grid.is_grid_empty(tile.row, tile.col) == false) {
            return false;
        }
    }
    return true;
}

void
game_s::lock_block() {
    std::vector<position_s> currentCheckedCell = current_block.get_cell_position();

    // Set the grid where the current block located to match the current block
    // color.
    // Also spawn Rectangle for the player to collide.

    update_grid_color(currentCheckedCell);

    update_landed_block_rect(currentCheckedCell);

    // TODO: handle player/enemy deaths here
    //

    // Update the block
    current_block = next_block;

    update_current_block_rect();

    // Instantly move block projection to the ground when created.
    update_projection();

    // prepare for the next block.
    next_block = get_random_block();

    grid.clear_full_row();
}
void
game_s::update_grid_color(std::vector<position_s> cell) {
    for (position_s pos : cell) {
        grid.update_grid_color(pos.row, pos.col, current_block.color_id);
    }
}
void
game_s::update_landed_block_rect(std::vector<position_s> cell) {
    for (position_s pos : cell) {
        landed_block_rect.push_back({
            (float)pos.col * config::cell_size + config::grid_offset_x, 
            (float)pos.row * config::cell_size + config::grid_offset_y, 
            config::cell_size, 
            config::cell_size
        });

    }
}


void
game_s::create_current_block_rect() {
    const std::vector<position_s>& curr_block_pos = current_block.get_cell_position();
    for (position_s pos : curr_block_pos) {
        current_block_rect.push_back(Rectangle {
            (float)pos.col * config::cell_size + config::grid_offset_x,
            (float)pos.row * config::cell_size + config::grid_offset_y,
            config::cell_size,
            config::cell_size,
        });
    }
}
void
game_s::clear_current_block_rect() {
    current_block_rect.clear();
}
void
game_s::update_current_block_rect() {
    clear_current_block_rect();
    create_current_block_rect();
}

void
game_s::update_projection() {
    block_projection = current_block;
    block_projection.color_id = 8;
    block_instant_move_down(block_projection);
}
void
game_s::update_projection_pos() {
    while (is_grid_occupied(block_projection) == false) {
        block_projection.move(-1, 0);
    }
}

void
game_s::debug_render_rect() {
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
game_s::is_block_outside(block_c& block) {
    std::vector<position_s> currentCheckedCell = block.get_cell_position();

    for (position_s cell_pos : currentCheckedCell) {
       if (grid.is_cell_outside(cell_pos.row, cell_pos.col)) {
          return true;
       }
    }

    return false;
}
