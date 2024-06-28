#include <raylib.h>

#include "game/game.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "game/config.hpp"

int main() {
    // Generate random seed.
    srand(time(nullptr));


    InitWindow(config::win_w, config::win_h, "Tetrush");
    SetTargetFPS(60);

    InitAudioDevice();
    std::cout << GetWorkingDirectory() << std::endl;

    ::game game;

    config::init_audio_res();

    PlayMusicStream(config::game_music);

    while (!WindowShouldClose()) {
    BeginDrawing();

        ClearBackground(DARKGRAY);
        game.render();
        game.update();

    EndDrawing();
    }

    config::deinit_audio_res();

    CloseAudioDevice();

    CloseWindow();
    return 0;
}
