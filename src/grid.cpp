#include <climits>
#include <raylib.h>
#include <iostream>

#include "colors.hpp"
#include "grid.hpp"

Grid::Grid() 
    : grid_cell {}
    , num_of_rows {20} //y
    , num_of_column {10}// x
    , cell_size {35}
    , colors {color::get_color()}
{}

void
Grid::debug() const {
    for (int y = 0; y < num_of_rows; y++) {
        for (int x = 0; x < num_of_column ; x++) {
            std::cout << grid_cell[y][x] << " ";
        }
        std::cout << std::endl;
    }
}


void
Grid::draw() const {
    for (int row = 0; row < num_of_rows; row++) {
        for (int col = 0; col < num_of_column; col++) {
            int cell_val = grid_cell[row][col];
            DrawRectangle(
                col * cell_size + 10,
                row * cell_size + 10,
                cell_size,
                cell_size,
                colors[cell_val]
            );
        }
    }
}

bool
Grid::is_cell_outside(int row, int col) {
    return !(row >= 0 && row < num_of_rows && col >= 0 && col < num_of_column);
}

bool
Grid::is_grid_empty(int row, int col) {
    return (grid_cell[row][col] == 0);
}

bool
Grid::is_row_full(int row) {

}