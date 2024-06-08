#ifndef GRID_HPP
#define GRID_HPP

#include "config.hpp"
#include <raylib.h>
#include <vector>

class Game;

class Grid {
public:
    Grid(Game& t_game);

    void Debug();
    void Draw();
    bool IsCellOutside(int row, int col);
    bool IsGridEmpty(int row, int col);

    void UpdateGridColor(int row, int col, int colorId);

    // Check if a row is full a cleared it up.
    bool IsRowFull(int row);
    void ClearRow(int row);

    // move a row down n times
    void MoveRowDown(int row, int nTimes);

    void MoveGridRowDown(int row, int nTimes);

    // The int returned from the method will be calculated for the score.
    int ClearFullRow();

public:
    int _gridCell[Config::NumOfRows][Config::NumOfCols]; // row, column or y. x
    int _cellSize;
    std::vector<Color> _colors;

private:
    // Game instance reference to manage the rect collider
    Game& _gameRef;
};


#endif // GRID_HPP
