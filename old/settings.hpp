// =======================================================================
// File Name : settings.hpp
// Author    :
// Purpose   : Constants to be used as input values in the game.
// TODO      :
// =======================================================================

#ifndef SETTINGS_HPP
#define SETTINGS_HPP

namespace settings {
    // = WINDOW SETTINGS =====================================================
    inline constexpr int ScreenWidth {1024};
    inline constexpr int ScreenHeight {720};
    inline constexpr int Fps {60};

    // = BOARD SETTINGS ======================================================
    inline constexpr Vec2<int> BoardPosition(250, 100);
    inline constexpr Vec2<int> BoardSize(10, 20); // Vec2(column, row)
    inline constexpr int CellSize {25};
    inline constexpr int PaddingSize {2};
};

#endif // SETTINGS_HPP
