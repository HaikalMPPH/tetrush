// =======================================================================
// File Name : game.cpp
// Author    :
// Purpose   : Game class implementation.
// TODO      :
// =======================================================================
#include "game.hpp"
#include <cassert>

Game::Game(const int w, const int h, const char* title) 
    : _board {
          settings::BoardPosition, 
          settings::BoardSize, 
          settings::CellSize, 
          settings::PaddingSize
      }
{
    // If window is not already openned.
    assert(!GetWindowHandle());
    SetTargetFPS(60);
    InitWindow(w, h, title);
}

Game::~Game() {
    // If window already openned.
    assert(GetWindowHandle());
    CloseWindow();
}

bool Game::GetGameIsClosable() const {
    return WindowShouldClose();
}

void Game::Tick() {
BeginDrawing();
    Update();
    Render();
EndDrawing();
}

void Game::Update() {
}

void Game::Render() {
    ClearBackground(LIGHTGRAY);
    _board.DrawBoard();
}
