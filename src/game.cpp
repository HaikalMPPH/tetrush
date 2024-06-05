#include <raylib.h>
#include <vector>
#include <cstdlib>
#include <iostream>

#include "game.hpp"
#include "block.hpp"
#include "config.hpp"
#include "position.hpp"
#include "tetromino.hpp"

Game::Game() 
  : grid {Grid(*this)}
  , ground_y {config::kCellSize * config::kNumOfRows + config::kGridOffsetY}
  , blocks {
      El(), Jay(), Straight(), 
      Square(), Tee(), SkewS(), 
      SkewZ()
    }
  , current_block {GetRandomBlock()}
  , next_block {GetRandomBlock()}
  , block_projection {current_block}
  , last_update_time {0.0}
  , player {*this}
{
  CreateCurrentBlockRect();
  UpdateProjection();
}

Block
Game::GetRandomBlock() {
  if (blocks.empty()) {
    blocks = CreateTetrominos();
  }

  // spawn random tetraminos from the list of tetrominos in game_s::blocks vector.
  const int rand_index = rand() % blocks.size();
  Block random_block = blocks[rand_index];
  
  // remove block from the block vector after randomly picked.
  blocks.erase(blocks.begin() + rand_index); // pointer arithmatics.
  
  return random_block;
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
  //debug_render_rect();
}

void
Game::Update() {
  player.Update();
  HandleInput();

  if (EventTriggered(0.5)) {
    BlockMoveDown(current_block);
    UpdateCurrentBlockRect();
  }

  UpdateCurrentBlockRect();
  UpdateProjection();

}

bool
Game::EventTriggered(double tick_interval) {
  double current_time = GetTime();

  // if the time passed the tick_interval
  if (current_time - last_update_time >= tick_interval) {
    last_update_time = current_time;
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
    player.HandleDeath();

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
  std::vector<Position> current_checked_cell = block.GetCellPositioin();

  for (Position tile : current_checked_cell) {
    if (grid.IsGridEmpty(tile.row, tile.col) == false) {
      return false;
    }
  }

  return true;
}

void
Game::LockBlock() {
  std::vector<Position> current_checked_cell = current_block.GetCellPositioin();

  // Set the grid where the current block located to match the current block
  // color.
  // Also spawn Rectangle for the player to collide.
  UpdateGridColor(current_checked_cell);
  UpdateLandedBlockRect(current_checked_cell);

  // TODO: handle player/enemy deaths here
  //

  // Update the block
  current_block = next_block;

  UpdateCurrentBlockRect();

  // Instantly Move block projection to the ground when created.
  UpdateProjection();

  // prepare for the next block.
  next_block = GetRandomBlock();

  grid.ClearFullRow();
}
void
Game::UpdateGridColor(std::vector<Position> cell) {
  for (Position pos : cell) {
    grid.UpdateGridColor(pos.row, pos.col, current_block.color_id);
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
  const std::vector<Position>& curr_block_pos = current_block.GetCellPositioin();
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
  block_projection.color_id = 8;
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

bool
Game::IsBlockOutside(Block& block) {
  std::vector<Position> current_checked_cell = block.GetCellPositioin();

  for (Position cell_pos : current_checked_cell) {
    if (grid.IsCellOutside(cell_pos.row, cell_pos.col)) {
      return true;
    }
  }

  return false;
}
