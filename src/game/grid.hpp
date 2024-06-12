#ifndef GRID_HPP
#define GRID_HPP

#include <raylib.h>
#include "config.hpp"
#include "../engine/utils/typedefs.hpp"

class Game;

class Grid {
public:
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

public:
    int grid_cell[Config::kNumOfRows][Config::kNumOfCols]; // row, column or y. x
    int cell_size;
    Vector<Color> colors;

private:
    // Game instance reference to manage the rect collider
    Game& game;
};


#endif // GRID_HPP
