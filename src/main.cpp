#include <raylib.h>

#include "game/game.hpp"
#include <cstdlib>
#include <ctime>

int main() {
    // Generate random seed.
    srand(time(nullptr));

    Game game;

    InitWindow(config::kWinW, config::kWinH, "Tetrush");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
    BeginDrawing();

        ClearBackground(DARKGRAY);
        game.render();
        game.update();

    EndDrawing();
    }

    CloseWindow();
    return 0;
}
