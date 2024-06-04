#include <raylib.h>
#include <iostream>

#include "colors.hpp"
#include "grid.hpp"
#include "config.hpp"
#include "game.hpp"

grid_s::grid_s(game_s& t_game) 
    : grid_cell {}
    , num_of_row {20} //y
    , num_of_col {10}// x
    , cell_size {config::cell_size}
    , colors {color::get_color()}
    , game_ref {t_game}
{}

void
grid_s::debug() const {
    for (int y = 0; y < num_of_row; y++) {
        for (int x = 0; x < num_of_col ; x++) {
            std::cout << grid_cell[y][x] << " ";
        }
        std::cout << std::endl;
    }
}

void grid_s::draw() const {
    for (int row = 0; row < num_of_row; row++) {
        for (int col = 0; col < num_of_col; col++) {
            int cell_val = grid_cell[row][col];
            DrawRectangle(
                col * cell_size + config::grid_offset_x,
                row * cell_size + config::grid_offset_y,
                cell_size,
                cell_size,
                colors[cell_val]
            );
        }
    }
}

bool
grid_s::is_cell_outside(int row, int col) {
    return !(row >= 0 && row < num_of_row && col >= 0 && col < num_of_col);
}

bool
grid_s::is_grid_empty(int row, int col) {
    return (grid_cell[row][col] == 0);
}

void 
grid_s::update_grid_color(int row, int col, int colorId) {
    grid_cell[row][col] = colorId;
}

bool
grid_s::is_row_full(int row) {
    for (int col = 0; col < num_of_col; col++) {
        if (grid_cell[row][col] == 0) {
            return false;
        }
    }

    return true;
}

void
grid_s::clear_row(int row) {
    // erase block
    for (int col = 0; col < num_of_col; col++) {
        grid_cell[row][col] = 0;

        // erase block collider
        for (int i = 0; i < game_ref.landed_block_rect.size(); i++) {
            if (game_ref.landed_block_rect[i].y == row * config::cell_size + config::grid_offset_y) {
                game_ref.landed_block_rect.erase(game_ref.landed_block_rect.begin() + i);
            }
        }
    }
}

void
grid_s::move_row_down(int row, int n_times) {
    for (int col = 0; col < num_of_col; col++) {
        grid_cell[row + n_times][col] = grid_cell[row][col];
        grid_cell[row][col] = 0;
    }

}

void
grid_s::move_grid_rect_down(int row, int n_times) {
    // Move down the corresponding rect with the same height n times
    for (int i = 0; i < game_ref.landed_block_rect.size(); i++) {
        if (game_ref.landed_block_rect[i].y == row * config::cell_size + config::grid_offset_y) {
            // std::cout << "MOVED!" << std::endl;
            game_ref.landed_block_rect[i].y += config::cell_size * n_times;
        }
    }
}

int
grid_s::clear_full_row() {
    int completed = 0;

    // start from the bottom row.
    for (int row = num_of_row - 1; row >= 0; row--) {
        if (is_row_full(row)) {
            clear_row(row);
            completed++;
        }
        else if (completed > 0) {
            move_row_down(row, completed);
            move_grid_rect_down(row, completed);
        }
    }

    return completed;
}
