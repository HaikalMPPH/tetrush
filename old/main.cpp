#include <iostream>
#include <raylib.h>

#include "game.hpp"
#include "settings.hpp"


int main() {
    Game game(
        settings::ScreenWidth, 
        settings::ScreenHeight, 
        "TetRush"
    );

    while (!game.GetGameIsClosable()) {
        game.Tick();
    }

    return 0;
}
