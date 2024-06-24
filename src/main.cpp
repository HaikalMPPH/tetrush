#include <raylib.h>

#include "game/game.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "game/config.hpp"

int main() {
    // Generate random seed.
    srand(time(nullptr));


    InitWindow(config::kWinW, config::kWinH, "Tetrush");
    SetTargetFPS(60);

    InitAudioDevice();
    std::cout << GetWorkingDirectory() << std::endl;

    Game game;

    config::initAudioRes();

    PlayMusicStream(config::kGameMusic);

    while (!WindowShouldClose()) {
    BeginDrawing();

        ClearBackground(DARKGRAY);
        game.render();
        game.update();

    EndDrawing();
    }

    config::deinitAudioRes();

    CloseAudioDevice();

    CloseWindow();
    return 0;
}
