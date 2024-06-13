#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <raylib.h>

namespace Config {
    constexpr int kWinW { 1024 };
    constexpr int kWinH { 720 };

    constexpr int kCellSize { 35 };
    constexpr int kNumOfRows { 20 };
    constexpr int kNumOfCols { 20 };

    constexpr float kGridOffsetX { kWinW / 6.f };
    constexpr float kGridOffsetY { 10.f };

    constexpr float kGameGravity { 10.f };
    constexpr float kGrondY { kCellSize * kNumOfRows + kGridOffsetY };

    constexpr Rectangle kLeftWallRect {
      0.f,
      0.f,
      kGridOffsetX,
      kWinH //- kGrondY
    };
    constexpr Rectangle kRightWallRect {
      kNumOfRows * kCellSize + kGridOffsetX, 
      0.f,
      kGridOffsetX,
      kWinH //- kGrondY
    };
    constexpr Rectangle kGroundRect {
      kGridOffsetX, 
      kGrondY,
      kNumOfRows * kCellSize,
      kWinH - kNumOfRows * kCellSize + kGridOffsetY //- kGrondY
    };
};

#endif
