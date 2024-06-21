#ifndef BLOCK_HPP
#define BLOCK_HPP

#include <raylib.h>

#include "../engine/utils/typedefs.hpp"
#include "position.hpp"

class Block {
public:
    Block();

    int color_id();
    void color_id(int colorId);

public:
    void draw();
    void move(int row, int col);

    void rotate();
    // For undoing if the block is out of bound when rotating.
    void undoRotate();

    std::vector<Position> getCellPosition();

protected:
    int color_id_; // It's used for color. Might change this later.
    int rotation_state_;
    Map<int, std::vector<Position>> cells_;
    int cell_size_;

    // for moving the block
    int row_offset_;
    int column_offset_;

    // Determine the color of the tetromino.
    std::vector<Color> color_;
};

#endif // BLOCK_HPP
