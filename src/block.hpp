#ifndef BLOCK_HPP
#define BLOCK_HPP

#include <map>
#include <vector>

#include <raylib.h>
#include "position.hpp"

class Block {
public:
    Block();

    int GetColorId();
    void SetColorId(int colorId);

public:
    void Draw();
    void Move(int row, int col);

    void Rotate();
    // For undoing if the block is out of bound when rotating.
    void UndoRotate();

    std::vector<Position> GetCellPosition();

protected:
    int color_id_; // It's used for color. Might change this later.
    int rotation_state_;
    std::map<int, std::vector<Position>> cells_;
    int cellsize_;

    // for moving the block
    int row_offset_;
    int column_offset_;

    // Determine the color of the tetromino.
    std::vector<Color> color_;
};

#endif // BLOCK_HPP
