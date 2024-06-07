#include <raylib.h>
#include <iostream>

#include "colors.hpp"
#include "grid.hpp"
#include "config.hpp"
#include "game.hpp"

Grid::Grid(::Game& game) 
    : grid_cell {}
    , cell_size {config::kCellSize}
    , colors {color::GetColor()}
    , game_ref_ {game}
{}

void
Grid::Debug() {
    for (int y = 0; y < config::kNumOfRows; y++) {
        for (int x = 0; x < config::kNumOfCols ; x++) {
            std::cout << grid_cell[y][x] << " ";
        }
        std::cout << std::endl;
    }
}

void Grid::Draw() {
    for (int row = 0; row < config::kNumOfRows; row++) {
        for (int col = 0; col < config::kNumOfCols; col++) {
            int cell_val = grid_cell[row][col];
            DrawRectangle(
                col * cell_size + config::kGridOffsetX,
                row * cell_size + config::kGridOffsetY,
                cell_size,
                cell_size,
                colors[cell_val]
            );
        }
    }
}

bool
Grid::IsCellOutside(int row, int col) {
    return !(row >= 0 && row < config::kNumOfRows && col >= 0 && col < config::kNumOfCols);
}

bool
Grid::IsGridEmpty(int row, int col) {
    return (grid_cell[row][col] == 0);
}

void 
Grid::UpdateGridColor(int row, int col, int colorId) {
    grid_cell[row][col] = colorId;
}

bool
Grid::IsRowFull(int row) {
    for (int col = 0; col < config::kNumOfCols; col++) {
        if (grid_cell[row][col] == 0) {
            return false;
        }
    }

    return true;
}

void
Grid::ClearRow(int row) {
    // erase block
    for (int col = 0; col < config::kNumOfCols; col++) {
        grid_cell[row][col] = 0;

        // erase block collider
        for (int i = 0; i < game_ref_.landed_block_rect.size(); i++) {
            if (game_ref_.landed_block_rect[i].y == row * config::kCellSize + config::kGridOffsetY) {
                game_ref_.landed_block_rect.erase(game_ref_.landed_block_rect.begin() + i);
            }
        }
    }
}

void
Grid::MoveRowDown(int row, int nTimes) {
    for (int col = 0; col < config::kNumOfCols; col++) {
        grid_cell[row + nTimes][col] = grid_cell[row][col];
        grid_cell[row][col] = 0;
    }

}

void
Grid::MoveGridRowDown(int row, int nTimes) {
    // Move down the corresponding rect with the same height n times
    for (int i = 0; i < game_ref_.landed_block_rect.size(); i++) {
        if (game_ref_.landed_block_rect[i].y == row * config::kCellSize + config::kGridOffsetY) {
            game_ref_.landed_block_rect[i].y += config::kCellSize * nTimes;
        }
    }
}

int
Grid::ClearFullRow() {
    int completed = 0;

    // start from the bottom row.
    for (int row = config::kNumOfRows - 1; row >= 0; row--) {
        if (IsRowFull(row)) {
            ClearRow(row);
            completed++;
        }
        else if (completed > 0) {
            MoveRowDown(row, completed);
            MoveGridRowDown(row, completed);
        }
    }

    return completed; // used for score.
}
