#ifndef BLOCK_HPP
#define BLOCK_HPP

#include <map>
#include <vector>

#include <raylib.h>
#include "position.hpp"

class Block {
public:
    Block();

    int GetColorId();
    void SetColorId(int colorId);

public:
    void Draw();
    void Move(int row, int col);

    void Rotate();
    // For undoing if the block is out of bound when rotating.
    void UndoRotate();

    std::vector<Position> GetCellPosition();

protected:
    int _colorId; // It's used for color. Might change this later.
    int _rotationState;
    std::map<int, std::vector<Position>> _cells;
    int _cellSize;

    // for moving the block
    int _rowOffset;
    int _columnOffset;

    // Determine the color of the tetromino.
    std::vector<Color> _color;
};

#endif // BLOCK_HPP
