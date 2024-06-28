#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <raylib.h>

namespace config {
    inline constexpr int win_w { 1600 };
    inline constexpr int win_h { 900 };

    inline constexpr int cell_size { 35 };
    inline constexpr int n_rows { 25 };
    inline constexpr int n_cols { 30 };

    inline constexpr float grid_off_x { win_w / 6.f };
    inline constexpr float grid_off_y { 10.f };

    inline constexpr float game_gravity { 10.f };
    inline constexpr float ground_y { cell_size * n_rows + grid_off_y };

    inline constexpr Rectangle l_wall_rect {
      0.f,
      0.f,
      grid_off_x,
      win_h //- kGrondY
    };
    inline constexpr Rectangle r_wall_rect {
      n_cols * cell_size + grid_off_x, 
      0.f,
      grid_off_x,
      win_h //- kGrondY
    };
    inline constexpr Rectangle ground_rect {
      grid_off_x, 
      ground_y,
      n_cols * cell_size,
      win_h - n_rows * cell_size + grid_off_y //- kGrondY
    };

    inline Sound player_jump_sound;
    inline Sound enemy_jump_sound;
    inline Sound game_over_sound;
    inline Sound enemy_killed_sound;
    inline Sound block_lock_sound;
    inline Sound row_completed_sound;
    inline Music game_music;

    inline void init_audio_res() {
      player_jump_sound = LoadSound("res/audio/player-jump.wav");
      enemy_jump_sound = LoadSound("res/audio/enemy-jump.wav");
      game_over_sound = LoadSound("res/audio/game-over.wav");
      enemy_killed_sound = LoadSound("res/audio/enemy-killed.wav");
      block_lock_sound = LoadSound("res/audio/block-lock.wav");
      row_completed_sound = LoadSound("res/audio/row-completed.wav");
      game_music = LoadMusicStream("res/audio/music.mp3");
    };
    inline void deinit_audio_res() {
      UnloadSound(player_jump_sound);
      UnloadSound(enemy_jump_sound);
      UnloadSound(game_over_sound);
      UnloadSound(enemy_killed_sound);
      UnloadSound(block_lock_sound);
      UnloadSound(row_completed_sound);
      UnloadMusicStream(game_music);
    }
};

#endif
