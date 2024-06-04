#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <raylib.h>

struct game_s;

struct player_s {
// = VARIABLES ===========================================================
    float speed;
    float vertical_speed;
    float jump_height;
    float player_size;
    Rectangle player_rect;
    float move_direction_x;
    float player_gravity;

    bool is_grounded;
    bool can_move;

    // The same height as the lowest grid 
    float ground_y;

    const game_s& game_ref;


// = METHODS =============================================================
    player_s(const game_s& game);

    void update();
    void render();

    void handle_input();

    void move_to_direction();
    void handle_gravity();
    void handle_wall_collision();
    void jump();

    void handle_rect_collision(const Rectangle& rect);
    void handle_landed_rect_collision();
    void handle_current_rect_collision();

    // Check if player is safe or not and only called in the Game::lock_block() method
    void handle_death();
};

#endif // PLAYER_HPP