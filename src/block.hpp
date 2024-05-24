#ifndef BLOCK_HPP
#define BLOCK_HPP

#include <map>
#include <vector>

#include <raylib.h>
#include "position.hpp"


// Rotation clockwise
enum BlockRotation {
    Up = 0,
    Right,
    Down,
    Left
};


class Block {
public:
    int color_id; // It's used for color. Might change this later.
    int rotation_state;
    std::map<int, std::vector<Position>> cells;
    int cell_size;

    // for moving the block
    int row_offset;
    int col_offset;

    // Determine the color of the tetromino.
    std::vector<Color> color;
public:
    Block();
    void draw();
    void move(int row, int col);

    void rotate();
    // For undoing if the block is out of bound when rotating.
    void undo_rotate();

    std::vector<Position> get_cell_position();
};

#endif // BLOCK_HPP
