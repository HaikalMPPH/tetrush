#include <cmath>
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
    , can_move {true}

    // Note: hardcoded num of rows. be careful when changing it in grid.cpp
    , ground_y {config::CellSize * 20 + config::GridOffsetY}
    , game_ref {game}
{}

void
Player::update() {
    handle_wall_collision();
    move_to_direction();
    handle_gravity();
    handle_landed_rect_collsion();
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

    // return gravity to normal.
    else {
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
Player::handle_landed_rect_collsion() {
    for (Rectangle rect : game_ref.landed_block_rect) {
        if (CheckCollisionRecs(player_rect, rect)) {
            // player & rect center point
            const Vector2 player_center {
                player_rect.x + player_size / 2.f,
                player_rect.y + player_size / 2.f,
            };
            const Vector2 rect_center {
                rect.x + config::CellSize / 2.f,
                rect.y + config::CellSize / 2.f,
            };

            // distance between the 2 centers
            const Vector2 center_delta = Vector2Subtract(player_center, rect_center);

            // half widths & heights
            const Vector2 player_halves {
                player_size / 2.f,
                player_size / 2.f,
            };
            const Vector2 rect_halves {
                config::CellSize / 2.f,
                config::CellSize / 2.f,
            };

            // seperate distance
            const float distX = player_halves.x + rect_halves.x - fabsf(center_delta.x);
            const float distY = player_halves.y + rect_halves.y - fabsf(center_delta.y);

            // collide from the sides.
            if (distX < distY) {
                player_rect.x += distX * (center_delta.x / fabsf(center_delta.x));
            }
            // collide from top or bottom
            else {
                player_rect.y += distY * (center_delta.y / fabsf(center_delta.y));
                vertical_speed = 0.f;

                // if player is above the rect it can jump
                if (player_center.y < rect_center.y) 
                    is_grounded = true;
            }
        }
    }
}
// TODO: handle_current_rect_collision here
//

void
Player::handle_death() {
    if (
        // player_rect.x + config::CellSize >= game_ref.min_danger_x &&
        // player_rect.x <= game_ref.max_danger_x &&
        player_rect.y + player_size >= game_ref.min_safe_y &&
        player_rect.y <= game_ref.max_safe_y
    ) {
        DrawText("GAME OVER", config::WinW / 2, config::WinH / 2, 30, BLACK);
        std::cout << "GAME OVER" << std::endl;
    }
}