#ifndef COLORS_HPP
#define COLORS_HPP

#include <vector>
#include <raylib.h>

namespace Colors {
  constexpr Color kEmpty = RAYWHITE;
  constexpr Color kRed = RED;
  constexpr Color kOrange = ORANGE;
  constexpr Color kYellow = YELLOW;
  constexpr Color kGreen = GREEN;
  constexpr Color kBlue = LIME;
  constexpr Color kCyan = SKYBLUE;
  constexpr Color kPurple = PURPLE;
  constexpr Color kProjectionGrey = Color {200, 200, 200, 125};

  std::vector<Color> getColor();
};
#endif // COLORS_HPP
