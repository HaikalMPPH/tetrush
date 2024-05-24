#ifndef COLORS_HPP
#define COLORS_HPP

#include <vector>
#include <raylib.h>

namespace color {
  constexpr Color Empty = RAYWHITE;
  constexpr Color Red = RED;
  constexpr Color Orange = ORANGE;
  constexpr Color Yellow = YELLOW;
  constexpr Color Green = GREEN;
  constexpr Color Blue = BLUE;
  constexpr Color Cyan = SKYBLUE;
  constexpr Color Purple = PURPLE;

  std::vector<Color> get_color();
};
#endif // COLORS_HPP
