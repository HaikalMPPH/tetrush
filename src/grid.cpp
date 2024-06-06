#include <raylib.h>
#include <iostream>

#include "colors.hpp"
#include "grid.hpp"
#include "config.hpp"
#include "game.hpp"

Grid::Grid(::Game& t_game) 
    : gridCell {}
    , cellSize {config::kCellSize}
    , colors {color::getColor()}
    , game {t_game}
{}

void
Grid::debug() {
    for (int y = 0; y < config::kNumOfRows; y++) {
        for (int x = 0; x < config::kNumOfCols ; x++) {
            std::cout << gridCell[y][x] << " ";
        }
        std::cout << std::endl;
    }
}

void Grid::draw() {
    for (int row = 0; row < config::kNumOfRows; row++) {
        for (int col = 0; col < config::kNumOfCols; col++) {
            int cell_val = gridCell[row][col];
            DrawRectangle(
                col * cellSize + config::kGridOffsetX,
                row * cellSize + config::kGridOffsetY,
                cellSize,
                cellSize,
                colors[cell_val]
            );
        }
    }
}

bool
Grid::isCellOutside(int row, int col) {
    return !(row >= 0 && row < config::kNumOfRows && col >= 0 && col < config::kNumOfCols);
}

bool
Grid::isGridEmpty(int row, int col) {
    return (gridCell[row][col] == 0);
}

void 
Grid::updateGridColor(int row, int col, int colorId) {
    gridCell[row][col] = colorId;
}

bool
Grid::isRowFull(int row) {
    for (int col = 0; col < config::kNumOfCols; col++) {
        if (gridCell[row][col] == 0) {
            return false;
        }
    }

    return true;
}

void
Grid::clearRow(int row) {
    // erase block
    for (int col = 0; col < config::kNumOfCols; col++) {
        gridCell[row][col] = 0;

        // erase block collider
        for (int i = 0; i < game.landedBlockRect.size(); i++) {
            if (game.landedBlockRect[i].y == row * config::kCellSize + config::kGridOffsetY) {
                game.landedBlockRect.erase(game.landedBlockRect.begin() + i);
            }
        }
    }
}

void
Grid::moveRowDown(int row, int n_times) {
    for (int col = 0; col < config::kNumOfCols; col++) {
        gridCell[row + n_times][col] = gridCell[row][col];
        gridCell[row][col] = 0;
    }

}

void
Grid::moveGridRowDown(int row, int n_times) {
    // Move down the corresponding rect with the same height n times
    for (int i = 0; i < game.landedBlockRect.size(); i++) {
        if (game.landedBlockRect[i].y == row * config::kCellSize + config::kGridOffsetY) {
            // std::cout << "MOVED!" << std::endl;
            game.landedBlockRect[i].y += config::kCellSize * n_times;
        }
    }
}

int
Grid::clearFullRow() {
    int completed = 0;

    // start from the bottom row.
    for (int row = config::kNumOfRows - 1; row >= 0; row--) {
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
