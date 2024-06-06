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
  Block getRandomBlock();

  std::vector<Block> createTetrominos();

  void render();
  void update();
  // * Trigger an event every certain tick (this is for moving the tetraminos down automatically).
  // * tick_interval: how many seconds before the event is triggered.
  bool eventTriggered(double tickInterval);

  void handleInput();


  // * Update the min and max x coordinate that will kill the player/enemy.
  // * Called every move_right or move_left and when spawning current_block. 
  void updateMinMaxDangerX();
  void resetDangerX();

  void blockMoveLeft(Block& block);
  void blockMoveRight(Block& block);
  void blockMoveDown(Block& block);
  void blockInstantMoveDown(Block& block);
  void currentBlockInstantMoveDownAndCheckDeath();
  void rotateBlock(Block& block);

  // Check if the grid next to/below the block is occupied.
  bool isGridOccupied(Block& block);

  // Called when the block reaches the ground.
  // Also processed if player/enemy is "squashable"
  void lockBlock();
  void updateGridColor(std::vector<Position> cell);
  void updateLandedBlockRect(std::vector<Position> cell);

  void createCurrentBlockRect();
  void clearCurrentBlockRect();
  void updateCurrentBlockRect();   // empty and recreate current_block_rect

  //
  void updateProjection();

  // DEBUG: render tetromino collider.
  void debugRenderRect();


  bool isBlockOutside(Block& block);

public:
  Grid grid;
  const float groundY;

  // list of the available tetraminos.
  std::vector<Block> blocks;
  Block currentBlock;
  Block nextBlock;

  // Tetramino projection.
  Block blockProjection;

  double lastUpdateTime;

  // Player
  Player player;

  // Vector of rect that the position is matched with the color grid.
  // The rect is used for the player collision
  std::vector<Rectangle> landedBlockRect;     // collider of a block that are on the ground.
  std::vector<Rectangle> currentBlockRect;    // collider of the current falling block.
};

#endif // GAME_HPP
