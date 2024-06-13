#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <raylib.h>

namespace config {
    constexpr int kWinW { 1600 };
    constexpr int kWinH { 900 };

    constexpr int kCellSize { 35 };
    constexpr int kNumOfRows { 25 };
    constexpr int kNumOfCols { 30 };

    constexpr float kGridOffsetX { kWinW / 6.f };
    constexpr float kGridOffsetY { 10.f };

    constexpr float kGameGravity { 10.f };
    constexpr float kGroundY { kCellSize * kNumOfRows + kGridOffsetY };

    constexpr Rectangle kLeftWallRect {
      0.f,
      0.f,
      kGridOffsetX,
      kWinH //- kGrondY
    };
    constexpr Rectangle kRightWallRect {
      kNumOfCols * kCellSize + kGridOffsetX, 
      0.f,
      kGridOffsetX,
      kWinH //- kGrondY
    };
    constexpr Rectangle kGroundRect {
      kGridOffsetX, 
      kGroundY,
      kNumOfCols * kCellSize,
      kWinH - kNumOfRows * kCellSize + kGridOffsetY //- kGrondY
    };
};

#endif
