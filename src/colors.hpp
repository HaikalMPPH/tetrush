#ifndef COLORS_HPP
#define COLORS_HPP

#include <vector>
#include <raylib.h>

namespace color {
// TODO: create custom color scheme and change the naming convention to all
// uppercase
  constexpr Color empty = RAYWHITE;
  constexpr Color red = RED;
  constexpr Color orange = ORANGE;
  constexpr Color yellow = YELLOW;
  constexpr Color green = GREEN;
  constexpr Color blue = BLUE;
  constexpr Color cyan = SKYBLUE;
  constexpr Color purple = PURPLE;
  constexpr Color projection_grey = Color {200, 200, 200, 125};

  std::vector<Color> get_color();
};
#endif // COLORS_HPP
