#ifndef CONFIG_HPP
#define CONFIG_HPP

namespace config {
    constexpr int WinW = 1024;
    constexpr int WinH = 720;

    constexpr int cell_size = 35;

    constexpr float GridOffsetX = WinW / 3.f;
    constexpr float GridOffsetY = 10.f;
};

#endif