// =======================================================================
// File Name : tetromino.hpp
// Author    :
// Purpose   : Class for creating tetris boards and cells.
// TODO      :
// =======================================================================

#ifndef TETROMINO_HPP
#define TETROMINO_HPP

#include <raylib.h>

class ITetromino {
public:
    virtual void Draw() = 0;
};

class TetrominoData {
private:
    TetrominoData();
    Color _color;
    bool _shapeArray[];
public:
};

#endif // TETROMINO_HPP
