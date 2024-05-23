// =======================================================================
// File Name : rl.cpp
// Author    :
// Purpose   : Implementation of rl.hpp 
// TODO      :
// =======================================================================

#include "rl.hpp"

void
rl::DrawRectangle(Vec2<int> position, Vec2<int> size, Color color) {
    assert(
        position.GetX() >= 0 && position.GetY() >= 0 &&
        position.GetX() < GetScreenWidth() && position.GetY() < GetScreenHeight()
    );

    DrawRectangle(position.GetX(), position.GetY(), size.GetX(), size.GetY(), color);
}

void 
rl::DrawRectangleLinesEx(Vec2<int> position, Vec2<int> size, int lineThickness, Color color) {
    DrawRectangleLinesEx(
        {(float)position.GetX(), (float)position.GetY(), (float)size.GetX(), (float)size.GetY()},
        lineThickness,
        color
    );
}
