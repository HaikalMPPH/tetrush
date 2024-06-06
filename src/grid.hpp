#ifndef GRID_HPP
#define GRID_HPP

#include "config.hpp"
#include <raylib.h>
#include <vector>

class Game;

class Grid {
public:
    int gridCell[config::kNumOfRows][config::kNumOfCols]; // row, column or y. x
    int cellSize;
    std::vector<Color> colors;

public:
    // Game instance reference to manage the rect collider
    Game& game;

    Grid(Game& t_game);

    void debug();
    void draw();
    bool isCellOutside(int row, int col);
    bool isGridEmpty(int row, int col);

    void updateGridColor(int row, int col, int colorId);

    // Check if a row is full a cleared it up.
    bool isRowFull(int row);
    void clearRow(int row);

    // move a row down n times
    void moveRowDown(int row, int nTimes);

    void moveGridRowDown(int row, int nTimes);

    // The int returned from the method will be calculated for the score.
    int clearFullRow();
};


#endif // GRID_HPP
