#include <raylib.h>
#include <vector>
#include <cstdlib>
#include <iostream>

#include "game.hpp"
#include "block.hpp"
#include "config.hpp"
#include "enemy.hpp"
#include "position.hpp"
#include "tetromino.hpp"

Game::Game() 
  : _grid {*this}
  , _groundY {Config::CellSize * Config::NumOfRows + Config::GridOffsetY}
  , _blocks {El(), Jay(), Straight(), Square(), Tee(), SkewS(), SkewZ()}
  , _currentBlock {PickRandomBlock()}
  , _nextBlock {PickRandomBlock()}
  , _blockProjection {_currentBlock}
  , _lastUpdateTime {0.0}
  , _enemySpawnCooldown {10.f}
  , _currentEnemySpawnCooldown {0.f}
  , _player {*this}
  , _enemies {}
  , _landedblockRect {}
  , _currentBlockRect {}
{
  CreateCurrentBlockRect();
  UpdateProjection();
}

Block
Game::PickRandomBlock() {
  if (_blocks.empty()) {
    _blocks = CreateTetrominos();
  }

  // spawn random tetraminos from the list of tetrominos in game_s::blocks vector.
  const int rand_index = rand() % _blocks.size();
  Block rand_block = _blocks[rand_index];
  
  // remove block from the block vector after randomly picked.
  _blocks.erase(_blocks.begin() + rand_index); // pointer arithmatics.
  
  return rand_block;
}

std::vector<Block>
Game::CreateTetrominos() {
  return {El(), Jay(), Straight(), Square(), Tee(), SkewS(), SkewZ()};
}

Enemy
Game::CreateEnemy() {
  const int maxX = Config::NumOfCols * Config::CellSize;
  const int randX = (rand() % maxX) + Config::GridOffsetX;

  return Enemy(*this, randX);
}
void
Game::AppendEnemy() {
  if (_currentEnemySpawnCooldown >= _enemySpawnCooldown) {
    _enemies.push_back(CreateEnemy());
    _currentEnemySpawnCooldown = 0.f;
  }

  _currentEnemySpawnCooldown += GetFrameTime();
}

void 
Game::Render() {
  _grid.Draw();
  _currentBlock.Draw();
  _blockProjection.Draw();
  _player.Render();
  for (Enemy& enemy : _enemies) {
    enemy.Render();
  }
}

void
Game::Update() {
  _player.Update();
  AppendEnemy();

  for (Enemy& enemy : _enemies) {
    enemy.Update();
  }

  HandleInput();

  if (EventTriggered(0.5)) {
    BlockMoveDown(_currentBlock);
    UpdateCurrentBlockRect();
  }

  UpdateCurrentBlockRect();
  UpdateProjection();

  _player.HandleDeath();
  for (Enemy& enemy : _enemies) {
    enemy.HandleDeath();
  }
}

bool
Game::EventTriggered(double tickInterval) {
  double currentTime = GetTime();

  // if the time passed the tick_interval
  if (currentTime - _lastUpdateTime >= tickInterval) {
    _lastUpdateTime = currentTime;
    return true;
  }

  return false;
}

void
Game::HandleInput() {
  int key = GetKeyPressed();

  switch (key) {
    case KEY_J:
      BlockMoveLeft(_currentBlock);
      break;
    case KEY_L:
      BlockMoveRight(_currentBlock);
      break;
    case KEY_K:
      CurrentBlockInstantMoveDownAndCheckDeath();
      LockBlock();
      break;
    case KEY_I:
      RotateBlock(_currentBlock);
      break;
  }

  _player.HandleInput();
}



void
Game::BlockMoveLeft(Block& block) {
  block.Move(0, -1);

  // if block out of bound to the left, Move the block 1 cell to the right.
  if (IsBlockOutside(block) || IsGridOccupied(block) == false) {
    block.Move(0, 1);
  }
}
void
Game::BlockMoveRight(Block& block) {
  block.Move(0, 1);

  if (IsBlockOutside(block) || IsGridOccupied(block) == false) {
    block.Move(0, -1);
  }
}
void
Game::BlockMoveDown(Block& block) {
  block.Move(1, 0);

  if (IsBlockOutside(block) || IsGridOccupied(block) == false) {
    block.Move(-1, 0);
    LockBlock();
  }
}
void
Game::BlockInstantMoveDown(Block& block) {
  while(true) {
    block.Move(1, 0);

    if (IsBlockOutside(block) || IsGridOccupied(block) == false) {
      block.Move(-1, 0);
      break;
    }
  }
}
void
Game::CurrentBlockInstantMoveDownAndCheckDeath() {
  while(true) {
    _currentBlock.Move(1, 0);

    UpdateCurrentBlockRect();

    if (!IsBlockOutside(_currentBlock)) {
      _player.HandleDeath();
      for (Enemy& enemy : _enemies) {
        enemy.HandleDeath();
      }
    }

    if (IsBlockOutside(_currentBlock) || IsGridOccupied(_currentBlock) == false) {
      _currentBlock.Move(-1, 0);
      break;
    }
  }
}



void
Game::RotateBlock(Block& block) {
  block.Rotate();

  if (IsBlockOutside(block) || IsGridOccupied(block) == false) {
    block.UndoRotate();
  }
}

bool
Game::IsGridOccupied(Block& block) {
  std::vector<Position> current_checked_cell = block.GetCellPosition();

  for (Position tile : current_checked_cell) {
    if (_grid.IsGridEmpty(tile.row, tile.col) == false) {
      return false;
    }
  }

  return true;
}
bool
Game::IsBlockOutside(Block& block) {
  std::vector<Position> current_checked_cell = block.GetCellPosition();

  for (Position cell_pos : current_checked_cell) {
    if (_grid.IsCellOutside(cell_pos.row, cell_pos.col)) {
      return true;
    }
  }

  return false;
}
void
Game::LockBlock() {
  std::vector<Position> current_checked_cell = _currentBlock.GetCellPosition();

  // Set the grid where the current block located to match the current block
  // color.
  // Also spawn Rectangle for the player to collide.
  UpdateGridColor(current_checked_cell);
  UpdateLandedBlockRect(current_checked_cell);

  // Update the block
  _currentBlock = _nextBlock;

  UpdateCurrentBlockRect();

  // Instantly Move block projection to the ground when created.
  UpdateProjection();

  // prepare for the next block.
  _nextBlock = PickRandomBlock();

  _grid.ClearFullRow();
}
void
Game::UpdateGridColor(std::vector<Position> cell) {
  for (Position pos : cell) {
    _grid.UpdateGridColor(pos.row, pos.col, _currentBlock.GetColorId());
  }
}
void
Game::UpdateLandedBlockRect(std::vector<Position> cell) {
  for (Position pos : cell) {
    _landedblockRect.push_back({
      (float)pos.col * Config::CellSize + Config::GridOffsetX, 
      (float)pos.row * Config::CellSize + Config::GridOffsetY, 
      Config::CellSize, 
      Config::CellSize
    });
  }
}


void
Game::CreateCurrentBlockRect() {
  const std::vector<Position>& curr_block_pos = _currentBlock.GetCellPosition();
  for (Position pos : curr_block_pos) {
    _currentBlockRect.push_back(Rectangle {
      (float)pos.col * Config::CellSize + Config::GridOffsetX,
      (float)pos.row * Config::CellSize + Config::GridOffsetY,
      Config::CellSize,
      Config::CellSize,
    });
  }
}
void
Game::ClearCurrentBlockRect() {
  _currentBlockRect.clear();
}
void
Game::UpdateCurrentBlockRect() {
  ClearCurrentBlockRect();
  CreateCurrentBlockRect();
}

void
Game::UpdateProjection() {
  _blockProjection = _currentBlock;
  _blockProjection.SetColorId(8);
  BlockInstantMoveDown(_blockProjection);
}

void
Game::DebugRenderRect() {
  // DEBUG: 
  // Render landed_block_rect
  for (Rectangle rect : _landedblockRect) {
    DrawRectangleRec(rect, PINK);
  }
  // Render current_block_rect
  for (Rectangle rect : _currentBlockRect) {
    DrawRectangleRec(rect, SKYBLUE);
  }
}

