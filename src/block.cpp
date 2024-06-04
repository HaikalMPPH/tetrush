#include <raylib.h>

#include "block.hpp"
#include "position.hpp"
#include "colors.hpp"
#include "config.hpp"

block_c::block_c() 
    : color_id {0}
    , rotation_state {BlockRotation::UP} // Default rotaion state.
    , cells {}
    , cell_size {config::cell_size} // match the grid cell_size
    , row_offset {0}
    , column_offset {0}
    , color {color::get_color()}
{}

void
block_c::draw() {
    // Const reference to make things cleaner
    for (position_s colorPos : get_cell_position()) {
        DrawRectangle(
            colorPos.col * cell_size + config::grid_offset_x, // following the grid offset. Change this later.
            colorPos.row * cell_size + 10,
            cell_size,
            cell_size,
            color[color_id]
        );
    }
}


void
block_c::move(int row, int col) {
    row_offset += row;
    column_offset += col;
}

void
block_c::rotate() {
    rotation_state++;

    if (rotation_state >= cells.size()) {
        rotation_state = 0;
    }
}

void 
block_c::undo_rotate() {
    rotation_state--;
    if (rotation_state < 0) {
        rotation_state = cells.size() - 1;
    }
}

std::vector<position_s>
block_c::get_cell_position() {
    std::vector<position_s> current_pos = cells[rotation_state];

    // note to self: moved_pos is always initialize to empty whenever this method is called. So
    // no, it won't continously adding position to the vector.
    std::vector<position_s> moved_pos {};

    for (position_s block_cell : current_pos) {
        position_s new_position = position_s(block_cell.row + row_offset,
                                         block_cell.col + column_offset);
        moved_pos.push_back(new_position);
    }

    return moved_pos;
}
