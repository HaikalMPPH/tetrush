#include <raylib.h>
#include <vector>
#include <cstdlib>
//#include <iostream>

#include "game.hpp"
#include "block.hpp"
#include "config.hpp"
#include "position.hpp"
#include "tetromino.hpp"

Game::Game() 
  : grid {*this}
  , ground_y {config::kCellSize * config::kNumOfRows + config::kGridOffsetY}
  , blocks {El(), Jay(), Straight(), Square(), Tee(), SkewS(), SkewZ()}
  , current_block {PickRandomBlock()}
  , next_block {PickRandomBlock()}
  , block_projection {current_block}
  , last_update_time {0.0}
  , player {*this}
  , enemies {}
  , landed_block_rect {}
  , current_block_rect {}
{
  CreateCurrentBlockRect();
  UpdateProjection();

  // NOTE: delete this later
  enemies.push_back(Enemy(*this));
}

Block
Game::PickRandomBlock() {
  if (blocks.empty()) {
    blocks = CreateTetrominos();
  }

  // spawn random tetraminos from the list of tetrominos in game_s::blocks vector.
  const int randIndex = rand() % blocks.size();
  Block randBlock = blocks[randIndex];
  
  // remove block from the block vector after randomly picked.
  blocks.erase(blocks.begin() + randIndex); // pointer arithmatics.
  
  return randBlock;
}

std::vector<Block>
Game::CreateTetrominos() {
  return {El(), Jay(), Straight(), Square(), Tee(), SkewS(), SkewZ()};
}

void 
Game::Render() {
  grid.Draw();
  current_block.Draw();
  block_projection.Draw();
  player.Render();
  for (Enemy enemy : enemies) {
    enemy.Render();
  }

  DebugRenderRect();
}

void
Game::Update() {
  player.Update();
  HandleInput();

  if (EventTriggered(0.5)) {
    BlockMoveDown(current_block);
    UpdateCurrentBlockRect();
  }

  //UpdateCurrentBlockRect();
  UpdateProjection();
  player.HandleDeath();
}

bool
Game::EventTriggered(double tickInterval) {
  double currentTime = GetTime();

  // if the time passed the tick_interval
  if (currentTime - last_update_time >= tickInterval) {
    last_update_time = currentTime;
    return true;
  }

  return false;
}

void
Game::HandleInput() {
  int key = GetKeyPressed();

  switch (key) {
    case KEY_J:
      BlockMoveLeft(current_block);
      break;
    case KEY_L:
      BlockMoveRight(current_block);
      break;
    case KEY_K:
      CurrentBlockInstantMoveDownAndCheckDeath();
      LockBlock();
      break;
    case KEY_I:
      RotateBlock(current_block);
      break;
  }

  player.HandleInput();
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
    current_block.Move(1, 0);

    UpdateCurrentBlockRect();
    if (!IsBlockOutside(current_block)) {
      player.HandleDeath();
    }

    if (IsBlockOutside(current_block) || IsGridOccupied(current_block) == false) {
      current_block.Move(-1, 0);
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
  std::vector<Position> currentCheckedCell = block.GetCellPosition();

  for (Position tile : currentCheckedCell) {
    if (grid.IsGridEmpty(tile.row, tile.col) == false) {
      return false;
    }
  }

  return true;
}
bool
Game::IsBlockOutside(Block& block) {
  std::vector<Position> currentCheckedCell = block.GetCellPosition();

  for (Position cellPos : currentCheckedCell) {
    if (grid.IsCellOutside(cellPos.row, cellPos.col)) {
      return true;
    }
  }

  return false;
}
void
Game::LockBlock() {
  std::vector<Position> currentCheckedCell = current_block.GetCellPosition();

  // Set the grid where the current block located to match the current block
  // color.
  // Also spawn Rectangle for the player to collide.
  UpdateGridColor(currentCheckedCell);
  UpdateLandedBlockRect(currentCheckedCell);

  // TODO: handle player/enemy deaths here
  //

  // Update the block
  current_block = next_block;

  UpdateCurrentBlockRect();

  // Instantly Move block projection to the ground when created.
  UpdateProjection();

  // prepare for the next block.
  next_block = PickRandomBlock();

  grid.ClearFullRow();
}
void
Game::UpdateGridColor(std::vector<Position> cell) {
  for (Position pos : cell) {
    grid.UpdateGridColor(pos.row, pos.col, current_block.GetColorId());
  }
}
void
Game::UpdateLandedBlockRect(std::vector<Position> cell) {
  for (Position pos : cell) {
    landed_block_rect.push_back({
      (float)pos.col * config::kCellSize + config::kGridOffsetX, 
      (float)pos.row * config::kCellSize + config::kGridOffsetY, 
      config::kCellSize, 
      config::kCellSize
    });
  }
}


void
Game::CreateCurrentBlockRect() {
  const std::vector<Position>& curr_block_pos = current_block.GetCellPosition();
  for (Position pos : curr_block_pos) {
    current_block_rect.push_back(Rectangle {
      (float)pos.col * config::kCellSize + config::kGridOffsetX,
      (float)pos.row * config::kCellSize + config::kGridOffsetY,
      config::kCellSize,
      config::kCellSize,
    });
  }
}
void
Game::ClearCurrentBlockRect() {
  current_block_rect.clear();
}
void
Game::UpdateCurrentBlockRect() {
  ClearCurrentBlockRect();
  CreateCurrentBlockRect();
}

void
Game::UpdateProjection() {
  block_projection = current_block;
  block_projection.SetColorId(8);
  BlockInstantMoveDown(block_projection);
}

void
Game::DebugRenderRect() {
  // DEBUG: 
  // Render landed_block_rect
  for (Rectangle rect : landed_block_rect) {
    DrawRectangleRec(rect, PINK);
  }
  // Render current_block_rect
  for (Rectangle rect : current_block_rect) {
    DrawRectangleRec(rect, SKYBLUE);
  }
}

