#include <raylib.h>
#include <iostream>

#include "colors.hpp"
#include "grid.hpp"
#include "config.hpp"
#include "game.hpp"

Grid::Grid(::Game& game) 
    : grid_cell {}
    , cell_size {Config::kCellSize}
    , colors {Colors::getColor()}
    , game {game}
{}

void
Grid::debug() {
    for (int y = 0; y < Config::kNumOfRows; y++) {
        for (int x = 0; x < Config::kNumOfCols ; x++) {
            std::cout << grid_cell[y][x] << " ";
        }
        std::cout << std::endl;
    }
}

void Grid::draw() {
    for (int row = 0; row < Config::kNumOfRows; row++) {
        for (int col = 0; col < Config::kNumOfCols; col++) {
            int cell_val = grid_cell[row][col];
            DrawRectangle(
                col * cell_size + Config::kGridOffsetX,
                row * cell_size + Config::kGridOffsetY,
                cell_size,
                cell_size,
                colors[cell_val]
            );
        }
    }
}

bool
Grid::isCellOutside(int row, int col) {
    return !(row >= 0 && row < Config::kNumOfRows && col >= 0 && col < Config::kNumOfCols);
}

bool
Grid::isGridEmpty(int row, int col) {
    return (grid_cell[row][col] == 0);
}

void 
Grid::updateGridColor(int row, int col, int colorId) {
    grid_cell[row][col] = colorId;
}

bool
Grid::isRowFull(int row) {
    for (int col = 0; col < Config::kNumOfCols; col++) {
        if (grid_cell[row][col] == 0) {
            return false;
        }
    }

    return true;
}

void
Grid::clearRow(int row) {
    // erase block
    for (int col = 0; col < Config::kNumOfCols; col++) {
        grid_cell[row][col] = 0;

        // erase block collider
        for (int i = 0; i < game.landed_block_rect.size(); i++) {
            if (game.landed_block_rect[i].y == row * Config::kCellSize + Config::kGridOffsetY) {
                game.landed_block_rect.erase(game.landed_block_rect.begin() + i);
            }
        }
    }
}

void
Grid::moveRowDown(int row, int nTimes) {
    for (int col = 0; col < Config::kNumOfCols; col++) {
        grid_cell[row + nTimes][col] = grid_cell[row][col];
        grid_cell[row][col] = 0;
    }

}

void
Grid::moveGridRowDown(int row, int nTimes) {
    // Move down the corresponding rect with the same height n times
    for (int i = 0; i < game.landed_block_rect.size(); i++) {
        if (game.landed_block_rect[i].y == row * Config::kCellSize + Config::kGridOffsetY) {
            game.landed_block_rect[i].y += Config::kCellSize * nTimes;
        }
    }
}

int
Grid::clearFullRow() {
    int completed = 0;

    // start from the bottom row.
    for (int row = Config::kNumOfRows - 1; row >= 0; row--) {
        if (isRowFull(row)) {
            clearRow(row);
            completed++;
        }
        else if (completed > 0) {
            moveRowDown(row, completed);
            moveGridRowDown(row, completed);
        }
    }

    return completed; // used for score.
}