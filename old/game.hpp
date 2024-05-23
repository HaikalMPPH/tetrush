// =======================================================================
// File Name : game.hpp
// Author    :
// Purpose   : Main game loop.
// TODO      :
// =======================================================================
#ifndef GAME_HPP
#define GAME_HPP

#include <raylib.h>
#include "board.hpp"
#include "settings.hpp"

class Game {
public:
    Game(const int w, const int h, const char* title);
    virtual ~Game();

    bool GetGameIsClosable() const;
    void Tick();
private:
    void Render();
    void Update();
private:
    Board _board;
};

#endif // GAME_HPP
