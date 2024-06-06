#include <raylib.h>

#include "block.hpp"
#include "position.hpp"
#include "colors.hpp"
#include "config.hpp"

Block::Block() 
    : colorId {0}
    , mCells {}
    , mCellSize {config::kCellSize} // match the grid cell_size
    , mRowOffset {0}
    , mColumnOffset {0}
    , mColor {color::getColor()}
{}

void
Block::draw() {
    // Const reference to make things cleaner
    for (Position color_pos : getCellPosition()) {
        DrawRectangle(
            color_pos.col * mCellSize + config::kGridOffsetX, // following the grid offset. Change this later.
            color_pos.row * mCellSize + 10,
            mCellSize,
            mCellSize,
            mColor[colorId]
        );
    }
}


void
Block::move(int row, int col) {
    mRowOffset += row;
    mColumnOffset += col;
}

void
Block::rotate() {
    mRotationState++;

    if (mRotationState >= mCells.size()) {
        mRotationState = 0;
    }
}

void 
Block::undoRotate() {
    mRotationState--;
    if (mRotationState < 0) {
        mRotationState = mCells.size() - 1;
    }
}

std::vector<Position>
Block::getCellPosition() {
    std::vector<Position> current_pos = mCells[mRotationState];

    // note to self: moved_pos is always initialize to empty whenever this method is called. So
    // no, it won't continously adding position to the vector.
    std::vector<Position> moved_pos {};

    for (Position block_cell : current_pos) {
        Position new_position = Position(block_cell.row + mRowOffset,
                                         block_cell.col + mColumnOffset);
        moved_pos.push_back(new_position);
    }

    return moved_pos;
}
