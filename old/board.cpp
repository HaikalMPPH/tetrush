// =======================================================================
// File Name : board.cpp
// Author    :
// Purpose   : board.hpp implementation.
// TODO      :
// =======================================================================
#include "board.hpp"
#include "rl.hpp"

Board::Cell::Cell() 
    : _exist {false}
    , _color {WHITE}
{
}

void
Board::Cell::SetColor(Color color) {
    _color = color;
    _exist = true;
}

Color 
Board::Cell::GetColor() const {
    return _color;
}

void
Board::Cell::Remove() {
    _exist = false;
}

Board::Board(Vec2<int> boardPosition, Vec2<int> size, int cellSize, const int padding) 
    : _boardPosition (boardPosition)
    , _width (size.GetX()) 
    , _height (size.GetY())
    , _cellSize (cellSize)
    , _padding (padding)
{
    // check for valid value.
    assert(_width > 0 && _height > 0 && _cellSize > 0);
    _cells.resize(_width * _height);
}

void
Board::SetCellColor(Vec2<int> pos, Color color) {
    // Cell posiiton (x, y) in _cells = _cells[_width * y + x].
    _cells[_width * pos.GetY() + pos.GetX()].SetColor(color);
}

void
Board::DrawCell(Vec2<int> pos) const {
    assert(pos.GetX() < _width && pos.GetY() < _height);

    Vec2<int> topLeft = _boardPosition + _padding + (pos * _cellSize);
    Color color = _cells[_width * pos.GetY() + pos.GetX()].GetColor();
    rl::DrawRectangle(
        topLeft,
        Vec2<int>(_cellSize, _cellSize) - _padding,
        color
    );
}

void
Board::DrawBorder() const {
    rl::DrawRectangleLinesEx(
        _boardPosition - (_cellSize / 2),
        Vec2((int)_width * _cellSize, (int)_height * _cellSize) + _cellSize,
        _cellSize / 2.f,
        GRAY
    );
}

void 
Board::DrawBoard() const {
    for (int y = 0; y < _height; y++) {
        for (int x = 0; x < _width; x++) {
            DrawCell(Vec2(x, y));
        }
    }

    DrawBorder();
}
