#include <raylib.h>

#include "block.hpp"
#include "position.hpp"
#include "colors.hpp"
#include "config.hpp"

Block::Block() 
    : color_id_ {0}
    , rotation_state_ {0}
    , cells_ {}
    , cellsize_ {config::kCellSize} // match the grid cell_size
    , row_offset_ {0}
    , column_offset_ {0}
    , color_ {color::GetColor()}
{}
int
Block::GetColorId() {
  return color_id_;
}
void
Block::SetColorId(int colorId) {
    color_id_ = colorId;
}


void
Block::Draw() {
    // Const reference to make things cleaner
    for (Position colorPos : GetCellPosition()) {
        DrawRectangle(
            colorPos.col * cellsize_ + config::kGridOffsetX, // following the grid offset. Change this later.
            colorPos.row * cellsize_ + 10,
            cellsize_,
            cellsize_,
            color_[GetColorId()]
        );
    }
}


void
Block::Move(int row, int col) {
    row_offset_ += row;
    column_offset_ += col;
}

void
Block::Rotate() {
    rotation_state_++;

    if (rotation_state_ >= cells_.size()) {
        rotation_state_ = 0;
    }
}

void 
Block::UndoRotate() {
    rotation_state_--;
    if (rotation_state_ < 0) {
        rotation_state_ = cells_.size() - 1;
    }
}

std::vector<Position>
Block::GetCellPosition() {
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
