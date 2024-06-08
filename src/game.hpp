#ifndef GAME_HPP
#define GAME_HPP

#include <raylib.h>
#include <vector>

#include "enemy.hpp"
#include "position.hpp"
#include "grid.hpp"
#include "block.hpp"
#include "player.hpp"

class Game {
public:
  Game();

public:
  Block PickRandomBlock();

  std::vector<Block> CreateTetrominos();
  Enemy CreateEnemy();
  void AppendEnemy();

  void Render();
  void Update();
  // * Trigger an event every certain tick (this is for moving the tetraminos down automatically).
  // * tick_interval: how many seconds before the event is triggered.
  bool EventTriggered(double tickInterval);

  void HandleInput();


  void BlockMoveLeft(Block& block);
  void BlockMoveRight(Block& block);
  void BlockMoveDown(Block& block);
  void BlockInstantMoveDown(Block& block);
  void CurrentBlockInstantMoveDownAndCheckDeath();
  void RotateBlock(Block& block);

  // Check if the grid next to/below the block is occupied.
  bool IsGridOccupied(Block& block);
  bool IsBlockOutside(Block& block);

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

public:
  Grid _grid;
  const float _groundY;

  // list of the available tetraminos.
  std::vector<Block> _blocks;
  Block _currentBlock;
  Block _nextBlock;

  // Tetramino projection.
  Block _blockProjection;

  double _lastUpdateTime;
  const float _enemySpawnCooldown;
  float _currentEnemySpawnCooldown;

  // Game entities
  Player _player;
  std::vector<Enemy> _enemies;

  // Vector of rect that the position is matched with the color grid.
  // The rect is used for the player collision
  std::vector<Rectangle> _landedblockRect;     // collider of a block that are on the ground.
  std::vector<Rectangle> _currentBlockRect;    // collider of the current falling block.
};

#endif // GAME_HPP
