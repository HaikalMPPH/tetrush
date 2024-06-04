#ifndef CONFIG_HPP
#define CONFIG_HPP

namespace config {
    constexpr int win_w = 1024;
    constexpr int win_h = 720;

    constexpr int cell_size = 35;

    constexpr float grid_offset_x = win_w / 3.f;
    constexpr float grid_offset_y = 10.f;
};

#endif