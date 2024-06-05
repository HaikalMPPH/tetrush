#ifndef GRID_HPP
#define GRID_HPP

#include "config.hpp"
#include <raylib.h>
#include <vector>

class Game;

class Grid {
public:
    int grid_cell[config::kNumOfRows][config::kNumOfCols]; // row, column or y. x
    int num_of_row;
    int num_of_col;
    int cell_size;
    std::vector<Color> colors;

public:
    // Game instance reference to manage the rect collider
    Game& game;

    Grid(Game& t_game);

    void Debug();
    void Draw();
    bool IsCellOutside(int row, int col);
    bool IsGridEmpty(int row, int col);

    void UpdateGridColor(int row, int col, int color_id);

    // Check if a row is full a cleared it up.
    bool IsRowFull(int row);
    void ClearRow(int row);

    // move a row down n times
    void MoveRowDown(int row, int n_times);

    void MoveGridRowDown(int row, int n_times);

    // The int returned from the method will be calculated for the score.
    int ClearFullRow();
};


#endif // GRID_HPP
