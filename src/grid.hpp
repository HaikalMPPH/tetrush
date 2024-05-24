#ifndef GRID_HPP
#define GRID_HPP

#include <raylib.h>
#include <vector>

struct Grid {
    int grid_cell[20][10]; // row, column or y. x
    int num_of_rows;
    int num_of_column;
    int cell_size;
    std::vector<Color> colors;

    Grid();
    void debug() const;
    void draw() const;
    bool is_cell_outside(int row, int col);
    bool is_grid_empty(int row, int col);

    // Check if a row is full a cleared it up.
    bool is_row_full(int row);
    void clear_row(int row);

    // move a row down n times
    void move_row_down(int row, int n_times);

    // The int returned from the method will be calculated for the score.
    int clear_full_row();
};

#endif // GRID_HPP
