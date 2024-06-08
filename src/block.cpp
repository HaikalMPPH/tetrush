#include <raylib.h>

#include "block.hpp"
#include "position.hpp"
#include "colors.hpp"
#include "config.hpp"

Block::Block() 
    : _colorId {0}
    , _rotationState {0}
    , _cells {}
    , _cellSize {Config::CellSize} // match the grid cell_size
    , _rowOffset {0}
    , _columnOffset {0}
    , _color {Colors::GetColor()}
{}
int
Block::GetColorId() {
  return _colorId;
}
void
Block::SetColorId(int colorId) {
    _colorId = colorId;
}


void
Block::Draw() {
    // Const reference to make things cleaner
    for (Position colorPos : GetCellPosition()) {
        DrawRectangle(
            colorPos.col * _cellSize + Config::GridOffsetX, // following the grid offset. Change this later.
            colorPos.row * _cellSize + 10,
            _cellSize,
            _cellSize,
            _color [GetColorId()]
        );
    }
}


void
Block::Move(int row, int col) {
    _rowOffset += row;
    _columnOffset += col;
}

void
Block::Rotate() {
    _rotationState++;

    if (_rotationState >= _cells.size()) {
        _rotationState = 0;
    }
}

void 
Block::UndoRotate() {
    _rotationState--;
    if (_rotationState < 0) {
        _rotationState = _cells.size() - 1;
    }
}

std::vector<Position>
Block::GetCellPosition() {
    std::vector<Position> currentPos = _cells[_rotationState];

    // note to self: moved_pos is always initialize to empty whenever this method is called. So
    // no, it won't continously adding position to the vector.
    std::vector<Position> movedPos {};

    for (Position blockCell : currentPos) {
        Position newPos = Position(blockCell.row + _rowOffset,
                                   blockCell.col + _columnOffset);
        movedPos.push_back(newPos);
    }

    return movedPos;
}
