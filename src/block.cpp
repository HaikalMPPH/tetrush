#include <raylib.h>

#include "block.hpp"
#include "colors.hpp"
#include "config.hpp"

Block::Block() 
    : color_id {0}
    , rotation_state {BlockRotation::Up} // Default rotaion state.
    , cells {}
    , cell_size {config::cell_size} // match the grid cell_size
    , row_offset {0}
    , col_offset {0}
    , color {color::get_color()}
{}

void
Block::draw() {
    // Const reference to make things cleaner
    for (Position color_pos : get_cell_position()) {
        DrawRectangle(
            color_pos.col * cell_size + config::GridOffsetX, // following the grid offset. Change this later.
            color_pos.row * cell_size + 10,
            cell_size,
            cell_size,
            color[color_id]
        );
    }
}


void
Block::move(int row, int col) {
    row_offset += row;
    col_offset += col;
}

void
Block::rotate() {
    rotation_state++;

    if (rotation_state >= cells.size()) {
        rotation_state = 0;
    }
}

void 
Block::undo_rotate() {
    rotation_state--;
    if (rotation_state < 0) {
        rotation_state = cells.size() - 1;
    }
}

std::vector<Position>
Block::get_cell_position() {
    std::vector<Position> current_pos = cells[rotation_state];

    // note to self: moved_pos is always initialize to empty whenever this method is called. So
    // no, it won't continously adding position to the vector.
    std::vector<Position> moved_pos {};

    for (Position block_cell : current_pos) {
        Position new_position = Position(block_cell.row + row_offset,
                                         block_cell.col + col_offset);
        moved_pos.push_back(new_position);
    }

    return moved_pos;
}
