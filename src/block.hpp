#ifndef BLOCK_HPP
#define BLOCK_HPP

#include <map>
#include <vector>

#include <raylib.h>
#include "position.hpp"

class Block {
public:
    Block();
    void draw();
    void move(int row, int col);

    void rotate();
    // For undoing if the block is out of bound when rotating.
    void undoRotate();

    std::vector<Position> getCellPosition();

public:
    int colorId; // It's used for color. Might change this later.

protected:
    int mRotationState;
    std::map<int, std::vector<Position>> mCells;
    int mCellSize;

    // for moving the block
    int mRowOffset;
    int mColumnOffset;

    // Determine the color of the tetromino.
    std::vector<Color> mColor;
};

#endif // BLOCK_HPP
