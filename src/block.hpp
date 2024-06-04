#ifndef BLOCK_HPP
#define BLOCK_HPP

#include <map>
#include <vector>

#include <raylib.h>
#include "position.hpp"

// Rotation clockwise
enum BlockRotation {
    UP = 0,
    RIGHT,
    DOWN,
    LEFT
};


class block_c {
public:
    int color_id; // It's used for color. Might change this later.
    int rotation_state;
    std::map<int, std::vector<position_s>> cells;
    int cell_size;

    // for moving the block
    int row_offset;
    int column_offset;

    // Determine the color of the tetromino.
    std::vector<Color> color;
public:
    block_c();
    void draw();
    void move(int row, int col);

    void rotate();
    // For undoing if the block is out of bound when rotating.
    void undo_rotate();

    std::vector<position_s> get_cell_position();
};

#endif // BLOCK_HPP
