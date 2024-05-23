// =======================================================================
// File Name : rl.hpp
// Author    :
// Purpose   : Custom raylib wrapper to support Vec2 data type.
// TODO      :
// =======================================================================

#ifndef RL_HPP
#define RL_HPP

#include <cassert>
#include <raylib.h>
#include "vec2.hpp"

namespace rl {
void DrawRectangle(Vec2<int> position, Vec2<int> size, Color color);
void DrawRectangleLinesEx(Vec2<int> position, Vec2<int> size, int lineThickness, Color color);
};

#endif // RL_HPP
