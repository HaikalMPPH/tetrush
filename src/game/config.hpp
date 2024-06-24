#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <raylib.h>

namespace config {
    inline constexpr int kWinW { 1600 };
    inline constexpr int kWinH { 900 };

    inline constexpr int kCellSize { 35 };
    inline constexpr int kNumOfRows { 25 };
    inline constexpr int kNumOfCols { 30 };

    inline constexpr float kGridOffsetX { kWinW / 6.f };
    inline constexpr float kGridOffsetY { 10.f };

    inline constexpr float kGameGravity { 10.f };
    inline constexpr float kGroundY { kCellSize * kNumOfRows + kGridOffsetY };

    inline constexpr Rectangle kLeftWallRect {
      0.f,
      0.f,
      kGridOffsetX,
      kWinH //- kGrondY
    };
    inline constexpr Rectangle kRightWallRect {
      kNumOfCols * kCellSize + kGridOffsetX, 
      0.f,
      kGridOffsetX,
      kWinH //- kGrondY
    };
    inline constexpr Rectangle kGroundRect {
      kGridOffsetX, 
      kGroundY,
      kNumOfCols * kCellSize,
      kWinH - kNumOfRows * kCellSize + kGridOffsetY //- kGrondY
    };

    inline Sound kPlayerJumpSound;
    inline Sound kEnemyJumpSound;
    inline Sound kGameOverSound;
    inline Sound kEnemyKilledSound;
    inline Sound kBlockLockSound;
    inline Sound kRowCompletedSound;
    inline Music kGameMusic;

    inline void initAudioRes() {
      kPlayerJumpSound = LoadSound("res/audio/player-jump.wav");
      kEnemyJumpSound = LoadSound("res/audio/enemy-jump.wav");
      kGameOverSound = LoadSound("res/audio/game-over.wav");
      kEnemyKilledSound = LoadSound("res/audio/enemy-killed.wav");
      kBlockLockSound = LoadSound("res/audio/block-lock.wav");
      kRowCompletedSound = LoadSound("res/audio/row-completed.wav");
      kGameMusic = LoadMusicStream("res/audio/music.mp3");
    };
    inline void deinitAudioRes() {
      UnloadSound(kPlayerJumpSound);
      UnloadSound(kEnemyJumpSound);
      UnloadSound(kGameOverSound);
      UnloadSound(kEnemyKilledSound);
      UnloadSound(kBlockLockSound);
      UnloadSound(kRowCompletedSound);
      UnloadMusicStream(kGameMusic);
    }
};

#endif
