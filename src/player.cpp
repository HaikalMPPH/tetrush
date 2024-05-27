#include <iostream>
#include <raylib.h>
#include <raymath.h>

#include "player.hpp"
#include "config.hpp"
#include "game.hpp"

Player::Player(const Game& game)
    : speed {200.f}
    , vertical_speed {0.f}
    , jump_height {-300.f}
    , player_size {config::CellSize / 2.f}
    , player_rect {config::WinW/2.f, 
                   config::WinH/2.f, 
                   player_size, 
                   player_size}
    , move_direction_x {0.f}
    , player_gravity {20.f}
    , is_grounded {false}
    // Note: hardcoded num of rows. be careful when changing it in grid.cpp
    , ground_y {config::CellSize * 20 + config::GridOffsetY}
    , game_ref {game}
{}

void
Player::update() {
    handle_wall_collision();
    move_to_direction();
    handle_gravity();
    handle_game_rect_collsion();
}

void
Player::render() {
    DrawRectangleRec(player_rect, RED);
}

void 
Player::handle_input() {
    if (IsKeyDown(KEY_A)) {
        move_direction_x = -1;
    }
    if (IsKeyDown(KEY_D)) {
        move_direction_x = 1;
    }
    if (IsKeyPressed(KEY_SPACE)) {
        jump();
    }
}

void
Player::move_to_direction() {
    player_rect.x += move_direction_x * speed * GetFrameTime();

    // reset to default after moving.
    move_direction_x = 0.f;
}

void
Player::handle_gravity() {
    vertical_speed += player_gravity;
    player_rect.y += vertical_speed * GetFrameTime();

    if (player_rect.y  + player_size >= ground_y) {
        is_grounded = true;
        vertical_speed = 0.f;
        player_gravity = 0.f;
        player_rect.y = ground_y - player_size;

    }
    else {
        // is_grounded = false;
        player_gravity = 10.f;
    }
}

void
Player::handle_wall_collision() {
    // Collision with left wall.
    if (player_rect.x <= config::GridOffsetX) {
        player_rect.x = config::GridOffsetX;
    }

    // Collision with right wall.
    else if (player_rect.x + player_size >= config::GridOffsetX + game_ref.grid.num_of_column * config::CellSize) {
        player_rect.x = (config::GridOffsetX + game_ref.grid.num_of_column * config::CellSize) - player_size;
    }
}

void
Player::jump() {
    if (is_grounded) {
        vertical_speed = jump_height;
        is_grounded = false;
    }
}

void
Player::handle_game_rect_collsion() {
    for (Rectangle rect : game_ref.grid_rect) {
        if (CheckCollisionRecs(player_rect, rect)) {
            // if collide from above
            if (
                player_rect.y + player_size >= rect.y &&
                player_rect.y < rect.y
            ) {
                // std::cout << "Collide from above" << std::endl;
                player_rect.y = rect.y - player_size;
                vertical_speed = 0.f;
                player_gravity = 0.f;
                is_grounded = true;
            }

            // if collide from left
            else if (
                player_rect.x + player_size >= rect.x &&
                player_rect.x + player_size < rect.x + config::CellSize &&
                player_rect.y + player_size >= rect.y
            ){
                player_rect.x = rect.x - player_size;
            }

            // if collide from right
            else if (
                player_rect.x <= rect.x + config::CellSize &&
                player_rect.x > rect.x &&
                player_rect.y + player_size >= rect.y
            ){
                // std::cout << "collide from right" << std::endl;
                player_rect.x = rect.x + config::CellSize;
            }
        }
    }
}

void
Player::handle_death() {
    // TODO: just use block_projection x and y (above the block_projection) coordinate 
    //       (scrap the projection rect)
    // TODO: remove this
    for (Rectangle kill_rect : game_ref.projection_rect) {
        if (
            player_rect.x >= kill_rect.x &&
            player_rect.x <= kill_rect.x + config::CellSize
        ) {
            std::cout << "Game Over" << std::endl;
            // TODO: make an
        }
    }
}