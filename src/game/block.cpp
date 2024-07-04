#include <raylib.h>

#include "block.hpp"
#include "position.hpp"
#include "colors.hpp"
#include "config.hpp"

block::block() 
    : color_id_ {0}
    , rotation_state_ {0}
    , cells_ {}
    , cell_size_ {config::cell_size} // match the grid cell_size
    , row_offset_ {0}
    , column_offset_ {config::n_cols / 2}
    , color_ {colors::get_color()}
{}
int
block::color_id() {
  return color_id_;
}
void
block::color_id(int color_id) {
    color_id_ = color_id;
}


void
block::draw() {
    for (::position color_pos : get_cell_position()) {
        DrawRectangle(
            color_pos.col * cell_size_ + config::grid_off_x, 
            color_pos.row * cell_size_ + 10,
            cell_size_,
            cell_size_,
            color_ [color_id()]
        );
    }
}


void
block::move(int row, int col) {
    row_offset_ += row;
    column_offset_ += col;
}

void
block::rotate() {
    rotation_state_++;

    if (rotation_state_ >= cells_.size()) {
        rotation_state_ = 0;
    }
}

void 
block::undo_rotate() {
    rotation_state_--;
    if (rotation_state_ < 0) {
        rotation_state_ = cells_.size() - 1;
    }
}

std::vector<::position>
block::get_cell_position() {
    std::vector<::position> currentPos = cells_[rotation_state_];
    std::vector<::position> movedPos {};

    for (::position blockCell : currentPos) {
        ::position newPos = ::position(blockCell.row + row_offset_,
                                   blockCell.col + column_offset_);
        movedPos.push_back(newPos);
    }

    return movedPos;
}
