#ifndef BLOCK_HPP
#define BLOCK_HPP

#include <vector>
#include <map>
#include <raylib.h>
#include "position.hpp"

class block {
public:
    block();

    int color_id();
    void color_id(int colorId);

public:
    void draw();
    void move(int row, int col);

    void rotate();
    // For undoing if the block is out of bound when rotating.
    void undo_rotate();

    std::vector<::position> get_cell_position();

protected:
    int color_id_; // It's used for color. Might change this later.
    int rotation_state_;
    std::map<int, std::vector<::position>> cells_;

    // for moving the block
    int row_offset_;
    int column_offset_;
};

#endif // BLOCK_HPP
