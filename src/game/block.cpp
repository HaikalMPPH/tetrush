#include <raylib.h>

#include "block.hpp"
#include "position.hpp"
#include "colors.hpp"
#include "config.hpp"

Block::Block() 
    : color_id_ {0}
    , rotation_state_ {0}
    , cells_ {}
    , cell_size_ {Config::kCellSize} // match the grid cell_size
    , row_offset_ {0}
    , column_offset_ {0}
    , color_ {Colors::getColor()}
{}
int
Block::color_id() {
  return color_id_;
}
void
Block::color_id(int colorId) {
    color_id_ = colorId;
}


void
Block::draw() {
    // Const reference to make things cleaner
    for (Position colorPos : getCellPosition()) {
        DrawRectangle(
            colorPos.col * cell_size_ + Config::kGridOffsetX, // following the grid offset. Change this later.
            colorPos.row * cell_size_ + 10,
            cell_size_,
            cell_size_,
            color_ [color_id()]
        );
    }
}


void
Block::move(int row, int col) {
    row_offset_ += row;
    column_offset_ += col;
}

void
Block::rotate() {
    rotation_state_++;

    if (rotation_state_ >= cells_.size()) {
        rotation_state_ = 0;
    }
}

void 
Block::undoRotate() {
    rotation_state_--;
    if (rotation_state_ < 0) {
        rotation_state_ = cells_.size() - 1;
    }
}

std::vector<Position>
Block::getCellPosition() {
    std::vector<Position> currentPos = cells_[rotation_state_];

    // note to self: moved_pos is always initialize to empty whenever this method is called. So
    // no, it won't continously adding position to the vector.
    std::vector<Position> movedPos {};

    for (Position blockCell : currentPos) {
        Position newPos = Position(blockCell.row + row_offset_,
                                   blockCell.col + column_offset_);
        movedPos.push_back(newPos);
    }

    return movedPos;
}
