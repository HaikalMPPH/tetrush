#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <raylib.h>

struct Game;

struct Player {
// = VARIABLES ===========================================================
    float speed;
    float vertical_speed;
    float jump_height;
    float player_size;
    Rectangle player_rect;
    float move_direction_x;
    float player_gravity;
    bool is_grounded;

    // The same height as the lowest grid 
    float ground_y;

    const Game& game_ref;


// = METHODS =============================================================
    Player(const Game& game);

    void update();
    void render();

    void handle_input();

    void move_to_direction();
    void handle_gravity();
    void handle_wall_collision();
    void jump();

    void handle_game_rect_collsion();
};

#endif // PLAYER_HPP