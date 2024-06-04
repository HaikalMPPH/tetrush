#ifndef GRID_HPP
#define GRID_HPP

#include <raylib.h>
#include <vector>

struct game_s;

struct grid_s {
    int grid_cell[20][10]; // row, column or y. x
    int num_of_row;
    int num_of_col;
    int cell_size;
    std::vector<Color> colors;

    // Game instance reference to manage the rect collider
    game_s& game_ref;

    grid_s(game_s& game);

    void debug() const;
    void draw() const;
    bool is_cell_outside(int row, int col);
    bool is_grid_empty(int row, int col);

    void update_grid_color(int row, int col, int color_id);

    // Check if a row is full a cleared it up.
    bool is_row_full(int row);
    void clear_row(int row);

    // move a row down n times
    void move_row_down(int row, int nTimes);

    void move_grid_rect_down(int row, int nTimes);

    // The int returned from the method will be calculated for the score.
    int clear_full_row();
};

#endif // GRID_HPP
