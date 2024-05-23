#include <raylib.h>

#include "game.hpp"
#include <cstdlib>
#include <ctime>

int main() {
    // Generate random seed.
    srand(time(nullptr));

    Game game;

    InitWindow(1024, 720, "Tetrush");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
    BeginDrawing();

        ClearBackground(DARKGRAY);
        game.draw();
        game.update();

    EndDrawing();
    }

    CloseWindow();
    return 0;
}
