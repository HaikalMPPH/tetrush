#ifndef CONFIG_HPP
#define CONFIG_HPP

namespace Config {
    constexpr int WinW = 1024;
    constexpr int WinH = 720;

    constexpr int CellSize = 35;
    constexpr int NumOfRows = 20;
    constexpr int NumOfCols = 20;

    constexpr float GridOffsetX = WinW / 6.f;
    constexpr float GridOffsetY = 10.f;

    constexpr float GameGravity = 10.f;
};

#endif
