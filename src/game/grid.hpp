#ifndef GRID_HPP
#define GRID_HPP

#include <raylib.h>
#include "config.hpp"
#include <vector>

class game;

class grid {
public:
    grid(::game* t_game);

    void draw();
    bool is_cell_outside(int row, int col);
    bool is_grid_empty(int row, int col);

    void update_grid_color(int row, int col, int colorId);

    // Check if a row is full a cleared it up.
    bool is_row_full(int row);
    void clear_row(int row);

    // move a row down n times
    void move_row_down(int row, int nTimes);

    void move_grid_row_down(int row, int nTimes);

    // The int returned from the method will be calculated for the score.
    int clear_full_row();

    void reset_color();

public:
    int grid_cell[config::n_rows][config::n_cols]; // row, column or y. x
    std::vector<Color> colors;

private:
    // ::Game instance reference to manage the rect collider
    ::game* game_ref;
};


#endif // GRID_HPP
