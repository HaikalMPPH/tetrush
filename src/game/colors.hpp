#ifndef COLORS_HPP
#define COLORS_HPP

#include <vector>
#include <raylib.h>

namespace colors {
  constexpr Color empty   = (Color) { 0xd7, 0xd7, 0xd8, 0xff };
  constexpr Color red     = (Color) { 0xfc, 0x5d, 0x7c, 0xff };
  constexpr Color orange  = (Color) { 0xf3, 0x96, 0x60, 0xff };
  constexpr Color yellow  = (Color) { 0xe7, 0xc6, 0x64, 0xff };
  constexpr Color green   = (Color) { 0xa9, 0xdc, 0x76, 0xff };
  constexpr Color blue    = (Color) { 0x78, 0xdc, 0xe6, 0xff };
  constexpr Color magenta = (Color) { 0xfd, 0x5f, 0xf0, 0xff };
  constexpr Color purple  = (Color) { 0xae, 0x81, 0xff, 0xff };
  constexpr Color grey    = (Color) { 0xc2, 0xc2, 0xc3, 0xff };

  std::vector<Color> get_color();
};
#endif // COLORS_HPP
