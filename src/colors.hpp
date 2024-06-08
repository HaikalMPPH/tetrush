#ifndef COLORS_HPP
#define COLORS_HPP

#include <vector>
#include <raylib.h>

namespace Colors {
  constexpr Color Empty = RAYWHITE;
  constexpr Color Red = RED;
  constexpr Color Orange = ORANGE;
  constexpr Color Yellow = YELLOW;
  constexpr Color Green = GREEN;
  constexpr Color Blue = LIME;
  constexpr Color Cran = SKYBLUE;
  constexpr Color Purple = PURPLE;
  constexpr Color ProjectionGrey = Color {200, 200, 200, 125};

  std::vector<Color> GetColor();
};
#endif // COLORS_HPP
