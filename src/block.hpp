#ifndef BLOCK_HPP
#define BLOCK_HPP

#include <map>
#include <vector>

#include <raylib.h>
#include "position.hpp"

    // Rotation clockwise
enum BlockRotation {
    up = 0,
    right,
    down,
    left
};


class Block {
public:
    int color_id; // It's used for color. Might change this later.
    int rotation_state;
    std::map<int, std::vector<Position>> cells;
    int cell_size;

    // for moving the block
    int row_offset;
    int column_offset;

    // Determine the color of the tetromino.
    std::vector<Color> color;
public:
    Block();
    void Draw();
    void Move(int row, int col);

    void Rotate();
    // For undoing if the block is out of bound when rotating.
    void UndoRotate();

    std::vector<Position> GetCellPositioin();
};

#endif // BLOCK_HPP
