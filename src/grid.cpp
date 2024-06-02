#include <climits>
#include <raylib.h>
#include <iostream>

#include "colors.hpp"
#include "grid.hpp"
#include "config.hpp"
#include "game.hpp"

Grid::Grid(Game& t_game) 
    : grid_cell {}
    , num_of_row {20} //y
    , num_of_column {10}// x
    , cell_size {config::CellSize}
    , colors {color::get_color()}
    , game {t_game}
{}

void
Grid::debug() const {
    for (int y = 0; y < num_of_row; y++) {
        for (int x = 0; x < num_of_column ; x++) {
            std::cout << grid_cell[y][x] << " ";
        }
        std::cout << std::endl;
    }
}

void Grid::draw() const {
    for (int row = 0; row < num_of_row; row++) {
        for (int col = 0; col < num_of_column; col++) {
            int cell_val = grid_cell[row][col];
            DrawRectangle(
                col * cell_size + config::GridOffsetX,
                row * cell_size + config::GridOffsetY,
                cell_size,
                cell_size,
                colors[cell_val]
            );
        }
    }
}

bool
Grid::is_cell_outside(int row, int col) {
    return !(row >= 0 && row < num_of_row && col >= 0 && col < num_of_column);
}

bool
Grid::is_grid_empty(int row, int col) {
    return (grid_cell[row][col] == 0);
}

bool
Grid::is_row_full(int row) {
    for (int col = 0; col < num_of_column; col++) {
        if (grid_cell[row][col] == 0) {
            return false;
        }
    }

    return true;
}

void
Grid::clear_row(int row) {
    // erase block
    for (int col = 0; col < num_of_column; col++) {
        grid_cell[row][col] = 0;

        // erase block collider
        for (int i = 0; i < game.landed_block_rect.size(); i++) {
            if (game.landed_block_rect[i].y == row * config::CellSize + config::GridOffsetY) {
                game.landed_block_rect.erase(game.landed_block_rect.begin() + i);
            }
        }
    }
}

void
Grid::move_row_down(int row, int n_times) {
    for (int col = 0; col < num_of_column; col++) {
        grid_cell[row + n_times][col] = grid_cell[row][col];
        grid_cell[row][col] = 0;
    }

}

void
Grid::move_grid_rect_down(int row, int n_times) {
    // Move down the corresponding rect with the same height n times
    for (int i = 0; i < game.landed_block_rect.size(); i++) {
        if (game.landed_block_rect[i].y == row * config::CellSize + config::GridOffsetY) {
            // std::cout << "MOVED!" << std::endl;
            game.landed_block_rect[i].y += config::CellSize * n_times;
        }
    }
}

int
Grid::clear_full_row() {
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



    // move_grid_rect_down(completed);

    return completed;
}