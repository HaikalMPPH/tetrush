#ifndef GAME_HPP
#define GAME_HPP

#include <raylib.h>
#include <vector>

#include "position.hpp"
#include "grid.hpp"
#include "block.hpp"
#include "player.hpp"

class Game {
public:
  Game();
  Block GetRandomBlock();

  std::vector<Block> CreateTetrominos();

  void Render();
  void Update();
  // * Trigger an event every certain tick (this is for moving the tetraminos down automatically).
  // * tick_interval: how many seconds before the event is triggered.
  bool EventTriggered(double tick_interval);

  void HandleInput();


  // * Update the min and max x coordinate that will kill the player/enemy.
  // * Called every move_right or move_left and when spawning current_block. 
  void UpdateMinMaxDangerX();
  void ResetDangerX();

  void BlockMoveLeft(Block& block);
  void BlockMoveRight(Block& block);
  void BlockMoveDown(Block& block);
  void BlockInstantMoveDown(Block& block);
  void CurrentBlockInstantMoveDownAndCheckDeath();
  void RotateBlock(Block& block);

  // Check if the grid next to/below the block is occupied.
  bool IsGridOccupied(Block& block);

  // Called when the block reaches the ground.
  // Also processed if player/enemy is "squashable"
  void LockBlock();
  void UpdateGridColor(std::vector<Position> cell);
  void UpdateLandedBlockRect(std::vector<Position> cell);

  void CreateCurrentBlockRect();
  void ClearCurrentBlockRect();
  void UpdateCurrentBlockRect();   // empty and recreate current_block_rect

  //
  void UpdateProjection();

  // DEBUG: render tetromino collider.
  void DebugRenderRect();


  bool IsBlockOutside(Block& block);

public:
  Grid grid;
  const float ground_y;

  // list of the available tetraminos.
  std::vector<Block> blocks;
  Block current_block;
  Block next_block;

  // Tetramino projection.
  Block block_projection;

  double last_update_time;

  // Player
  Player player;

  // Vector of rect that the position is matched with the color grid.
  // The rect is used for the player collision
  std::vector<Rectangle> landed_block_rect;     // collider of a block that are on the ground.
  std::vector<Rectangle> current_block_rect;    // collider of the current falling block.
};

#endif // GAME_HPP
