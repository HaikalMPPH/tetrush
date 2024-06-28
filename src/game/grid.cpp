#include <raylib.h>
#include <iostream>

#include "colors.hpp"
#include "grid.hpp"
#include "config.hpp"
#include "game.hpp"

grid::grid(::game& game) 
    : grid_cell {}
    , cell_size {config::cell_size}
    , colors {colors::get_color()}
    , game_ref {game}
{}

void
grid::debug() {
    for (int y = 0; y < config::n_rows; y++) {
        for (int x = 0; x < config::n_cols ; x++) {
            std::cout << grid_cell[y][x] << " ";
        }
        std::cout << std::endl;
    }
}

void grid::draw() {
    for (int row = 0; row < config::n_rows; row++) {
        for (int col = 0; col < config::n_cols; col++) {
            int cell_val = grid_cell[row][col];
            DrawRectangle(
                col * cell_size + config::grid_off_x,
                row * cell_size + config::grid_off_y,
                cell_size,
                cell_size,
                colors[cell_val]
            );
        }
    }
}

bool
grid::is_cell_outside(int row, int col) {
    return !(row >= 0 && row < config::n_rows && col >= 0 && col < config::n_cols);
}

bool
grid::is_grid_empty(int row, int col) {
    return (grid_cell[row][col] == 0);
}

void 
grid::update_grid_color(int row, int col, int colorId) {
    grid_cell[row][col] = colorId;
}

bool
grid::is_row_full(int row) {
    for (int col = 0; col < config::n_cols; col++) {
        if (grid_cell[row][col] == 0) {
            return false;
        }
    }

    return true;
}

void
grid::clear_row(int row) {
    // erase block
    for (int col = 0; col < config::n_cols; col++) {
        grid_cell[row][col] = 0;

        // erase block collider
        for (int i = 0; i < game_ref.landed_block_rect.size(); i++) {
            if (game_ref.landed_block_rect[i].y == row * config::cell_size + config::grid_off_y) {
                game_ref.landed_block_rect.erase(game_ref.landed_block_rect.begin() + i);
            }
        }
    }
}

void
grid::move_row_down(int row, int nTimes) {
    for (int col = 0; col < config::n_cols; col++) {
        grid_cell[row + nTimes][col] = grid_cell[row][col];
        grid_cell[row][col] = 0;
    }

}

void
grid::move_grid_row_down(int row, int nTimes) {
    // Move down the corresponding rect with the same height n times
    for (int i = 0; i < game_ref.landed_block_rect.size(); i++) {
        if (game_ref.landed_block_rect[i].y == row * config::cell_size + config::grid_off_y) {
            game_ref.landed_block_rect[i].y += config::cell_size * nTimes;
        }
    }
}

int
grid::clear_full_row() {
    int completed = 0;

    // start from the bottom row.
    for (int row = config::n_rows - 1; row >= 0; row--) {
        if (is_row_full(row)) {
            clear_row(row);
            completed++;
        }
        else if (completed > 0) {
            move_row_down(row, completed);
            move_grid_row_down(row, completed);
        }
    }

    if (completed > 0) {
      PlaySound(config::row_completed_sound);
    }

    return completed; // used for score.
}

void
grid::reset_color() {
  for (int row = 0; row < config::n_rows; row++) {
    for (int col = 0; col < config::n_cols; col++) {
      grid_cell[row][col] = 0;
    }
  }
}
