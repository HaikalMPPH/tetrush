#include <raylib.h>
#include <iostream>

#include "colors.hpp"
#include "grid.hpp"
#include "config.hpp"
#include "game.hpp"

Grid::Grid(::Game& game) 
    : _gridCell {}
    , _cellSize {Config::CellSize}
    , _colors {Colors::GetColor()}
    , _gameRef {game}
{}

void
Grid::Debug() {
    for (int y = 0; y < Config::NumOfRows; y++) {
        for (int x = 0; x < Config::NumOfCols ; x++) {
            std::cout << _gridCell[y][x] << " ";
        }
        std::cout << std::endl;
    }
}

void Grid::Draw() {
    for (int row = 0; row < Config::NumOfRows; row++) {
        for (int col = 0; col < Config::NumOfCols; col++) {
            int cell_val = _gridCell[row][col];
            DrawRectangle(
                col * _cellSize + Config::GridOffsetX,
                row * _cellSize + Config::GridOffsetY,
                _cellSize,
                _cellSize,
                _colors[cell_val]
            );
        }
    }
}

bool
Grid::IsCellOutside(int row, int col) {
    return !(row >= 0 && row < Config::NumOfRows && col >= 0 && col < Config::NumOfCols);
}

bool
Grid::IsGridEmpty(int row, int col) {
    return (_gridCell[row][col] == 0);
}

void 
Grid::UpdateGridColor(int row, int col, int colorId) {
    _gridCell[row][col] = colorId;
}

bool
Grid::IsRowFull(int row) {
    for (int col = 0; col < Config::NumOfCols; col++) {
        if (_gridCell[row][col] == 0) {
            return false;
        }
    }

    return true;
}

void
Grid::ClearRow(int row) {
    // erase block
    for (int col = 0; col < Config::NumOfCols; col++) {
        _gridCell[row][col] = 0;

        // erase block collider
        for (int i = 0; i < _gameRef._landedblockRect.size(); i++) {
            if (_gameRef._landedblockRect[i].y == row * Config::CellSize + Config::GridOffsetY) {
                _gameRef._landedblockRect.erase(_gameRef._landedblockRect.begin() + i);
            }
        }
    }
}

void
Grid::MoveRowDown(int row, int nTimes) {
    for (int col = 0; col < Config::NumOfCols; col++) {
        _gridCell[row + nTimes][col] = _gridCell[row][col];
        _gridCell[row][col] = 0;
    }

}

void
Grid::MoveGridRowDown(int row, int nTimes) {
    // Move down the corresponding rect with the same height n times
    for (int i = 0; i < _gameRef._landedblockRect.size(); i++) {
        if (_gameRef._landedblockRect[i].y == row * Config::CellSize + Config::GridOffsetY) {
            _gameRef._landedblockRect[i].y += Config::CellSize * nTimes;
        }
    }
}

int
Grid::ClearFullRow() {
    int completed = 0;

    // start from the bottom row.
    for (int row = Config::NumOfRows - 1; row >= 0; row--) {
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
