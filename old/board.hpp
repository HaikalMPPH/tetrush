// =======================================================================
// File Name : board.hpp
// Author    :
// Purpose   : Class for creating tetris boards and cells.
// TODO      :
// =======================================================================
#ifndef BOARD_HPP
#define BOARD_HPP

#include <vector>
#include <cassert>
#include "vec2.hpp"
#include "rl.hpp"

class Board {
private:
    class Cell {
    private:
        bool _exist;
        Color _color;
    public:
        Cell();
        void SetColor(Color color);
        Color GetColor() const;
        void Remove();
    };
private:
    std::vector<Cell> _cells;
    Vec2<int> _boardPosition;
    const unsigned int _width;
    const unsigned int _height;
    const int _cellSize;
    const unsigned int _padding;
public:
    // size: Vec2(column, row);
    Board(Vec2<int> boardPosition, Vec2<int> size, int cellSize, const int padding);

    void SetCellColor(Vec2<int> pos, Color color);
    void DrawCell(Vec2<int> pos) const;
    void DrawBorder() const;
    void DrawBoard() const;
};

#endif // BOARD_HPP
