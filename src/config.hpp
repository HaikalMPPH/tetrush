#ifndef CONFIG_HPP
#define CONFIG_HPP

namespace config {
    constexpr int kWinW = 1024;
    constexpr int kWinH = 720;

    constexpr int kCellSize = 35;
    constexpr int kNumOfRows = 20;
    constexpr int kNumOfCols = 20;

    constexpr float kGridOffsetX = kWinW / 6.f;
    constexpr float kGridOffsetY = 10.f;

    constexpr float kGameGravity = 10.f;
};

#endif
