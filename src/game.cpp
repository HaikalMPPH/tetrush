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
  , groundY {config::kCellSize * config::kNumOfRows + config::kGridOffsetY}
  , blocks {
      El(), Jay(), Straight(), 
      Square(), Tee(), SkewS(), 
      SkewZ()
    }
  , currentBlock {getRandomBlock()}
  , nextBlock {getRandomBlock()}
  , blockProjection {currentBlock}
  , lastUpdateTime {0.0}
  , player {*this}
{
  createCurrentBlockRect();
  updateProjection();
}

Block
Game::getRandomBlock() {
  if (blocks.empty()) {
    blocks = createTetrominos();
  }

  // spawn random tetraminos from the list of tetrominos in game_s::blocks vector.
  const int rand_index = rand() % blocks.size();
  Block random_block = blocks[rand_index];
  
  // remove block from the block vector after randomly picked.
  blocks.erase(blocks.begin() + rand_index); // pointer arithmatics.
  
  return random_block;
}

std::vector<Block>
Game::createTetrominos() {
  return {El(), Jay(), Straight(), Square(), Tee(), SkewS(), SkewZ()};
}

void 
Game::render() {
  grid.draw();
  currentBlock.draw();
  blockProjection.draw();
  player.Render();
  //debug_render_rect();
}

void
Game::update() {
  player.Update();
  handleInput();

  if (eventTriggered(0.5)) {
    blockMoveDown(currentBlock);
    updateCurrentBlockRect();
  }

  updateCurrentBlockRect();
  updateProjection();

}

bool
Game::eventTriggered(double tick_interval) {
  double current_time = GetTime();

  // if the time passed the tick_interval
  if (current_time - lastUpdateTime >= tick_interval) {
    lastUpdateTime = current_time;
    return true;
  }

  return false;
}

void
Game::handleInput() {
  int key = GetKeyPressed();

  switch (key) {
    case KEY_J:
      blockMoveLeft(currentBlock);
      break;
    case KEY_L:
      blockMoveRight(currentBlock);
      break;
    case KEY_K:
      currentBlockInstantMoveDownAndCheckDeath();
      lockBlock();
      break;
    case KEY_I:
      rotateBlock(currentBlock);
      break;
  }

  player.HandleInput();
}



void
Game::blockMoveLeft(Block& block) {
  block.move(0, -1);

  // if block out of bound to the left, Move the block 1 cell to the right.
  if (isBlockOutside(block) || isGridOccupied(block) == false) {
    block.move(0, 1);
  }
}
void
Game::blockMoveRight(Block& block) {
  block.move(0, 1);

  if (isBlockOutside(block) || isGridOccupied(block) == false) {
    block.move(0, -1);
  }
}
void
Game::blockMoveDown(Block& block) {
  block.move(1, 0);

  if (isBlockOutside(block) || isGridOccupied(block) == false) {
    block.move(-1, 0);
    lockBlock();
  }
}
void
Game::blockInstantMoveDown(Block& block) {
  while(true) {
    block.move(1, 0);

    if (isBlockOutside(block) || isGridOccupied(block) == false) {
      block.move(-1, 0);
      break;
    }
  }
}
void
Game::currentBlockInstantMoveDownAndCheckDeath() {
  while(true) {
    currentBlock.move(1, 0);

    updateCurrentBlockRect();
    player.HandleDeath();

    if (isBlockOutside(currentBlock) || isGridOccupied(currentBlock) == false) {
      currentBlock.move(-1, 0);
      break;
    }
  }
}



void
Game::rotateBlock(Block& block) {
  block.rotate();

  if (isBlockOutside(block) || isGridOccupied(block) == false) {
    block.undoRotate();
  }
}

bool
Game::isGridOccupied(Block& block) {
  std::vector<Position> current_checked_cell = block.getCellPosition();

  for (Position tile : current_checked_cell) {
    if (grid.isGridEmpty(tile.row, tile.col) == false) {
      return false;
    }
  }

  return true;
}

void
Game::lockBlock() {
  std::vector<Position> current_checked_cell = currentBlock.getCellPosition();

  // Set the grid where the current block located to match the current block
  // color.
  // Also spawn Rectangle for the player to collide.
  updateGridColor(current_checked_cell);
  updateLandedBlockRect(current_checked_cell);

  // TODO: handle player/enemy deaths here
  //

  // Update the block
  currentBlock = nextBlock;

  updateCurrentBlockRect();

  // Instantly Move block projection to the ground when created.
  updateProjection();

  // prepare for the next block.
  nextBlock = getRandomBlock();

  grid.clearFullRow();
}
void
Game::updateGridColor(std::vector<Position> cell) {
  for (Position pos : cell) {
    grid.updateGridColor(pos.row, pos.col, currentBlock.colorId);
  }
}
void
Game::updateLandedBlockRect(std::vector<Position> cell) {
  for (Position pos : cell) {
    landedBlockRect.push_back({
      (float)pos.col * config::kCellSize + config::kGridOffsetX, 
      (float)pos.row * config::kCellSize + config::kGridOffsetY, 
      config::kCellSize, 
      config::kCellSize
    });
  }
}


void
Game::createCurrentBlockRect() {
  const std::vector<Position>& curr_block_pos = currentBlock.getCellPosition();
  for (Position pos : curr_block_pos) {
    currentBlockRect.push_back(Rectangle {
      (float)pos.col * config::kCellSize + config::kGridOffsetX,
      (float)pos.row * config::kCellSize + config::kGridOffsetY,
      config::kCellSize,
      config::kCellSize,
    });
  }
}
void
Game::clearCurrentBlockRect() {
  currentBlockRect.clear();
}
void
Game::updateCurrentBlockRect() {
  clearCurrentBlockRect();
  createCurrentBlockRect();
}

void
Game::updateProjection() {
  blockProjection = currentBlock;
  blockProjection.colorId = 8;
  blockInstantMoveDown(blockProjection);
}

void
Game::debugRenderRect() {
  // DEBUG: 
  // Render landed_block_rect
  for (Rectangle rect : landedBlockRect) {
    DrawRectangleRec(rect, PINK);
  }
  // Render current_block_rect
  for (Rectangle rect : currentBlockRect) {
    DrawRectangleRec(rect, SKYBLUE);
  }
}

bool
Game::isBlockOutside(Block& block) {
  std::vector<Position> current_checked_cell = block.getCellPosition();

  for (Position cell_pos : current_checked_cell) {
    if (grid.isCellOutside(cell_pos.row, cell_pos.col)) {
      return true;
    }
  }

  return false;
}
