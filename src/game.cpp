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
#include "colors.hpp"

Game::Game() 
  : grid {*this}
  , score {0}
  , ground_y {Config::kCellSize * Config::kNumOfRows + Config::kGridOffsetY}
  , block {El(), Jay(), Straight(), Square(), Tee(), SkewS(), SkewZ()}
  , current_block {pickRandomBlock()}
  , next_block {pickRandomBlock()}
  , block_projection {current_block}
  , last_update_time {0.0}
  , enemy_spawn_cooldown {10.f}
  , current_enemy_spawn_cooldown {0.f}
  , player {this}
  , enemies {}
  , landed_block_rect {}
  , current_block_rect {}
{
  createCurrentBlockRect();
  updateProjection();
}
Game::~Game() {
  for (Enemy* enemy : enemies) {
    delete enemy;
  }
}

Block
Game::pickRandomBlock() {
  if (block.empty()) {
    block = createTetrominos();
  }

  // spawn random tetraminos from the list of tetrominos in game_s::blocks vector.
  const int rand_index = rand() % block.size();
  Block rand_block = block[rand_index];
  
  // remove block from the block vector after randomly picked.
  block.erase(block.begin() + rand_index); // pointer arithmatics.
  
  return rand_block;
}

Vector<Block>
Game::createTetrominos() {
  return {El(), Jay(), Straight(), Square(), Tee(), SkewS(), SkewZ()};
}

Enemy*
Game::createEnemy() {
  const int maxX = Config::kNumOfCols * Config::kCellSize;
  const int randX = (rand() % maxX) + Config::kGridOffsetX;

  // DEBUG:
  std::cout << "Enemy spawned!" << std::endl; 

  return new Enemy(this, randX);
}
void
Game::appendEnemy() {
  if (current_enemy_spawn_cooldown >= enemy_spawn_cooldown) {
    enemies.push_back(createEnemy());
    current_enemy_spawn_cooldown = 0.f;
  }

  current_enemy_spawn_cooldown += GetFrameTime();
}

void 
Game::render() {
  grid.draw();

  // Score
  DrawText(
    std::to_string(score).c_str(), 
    Config::kWinW / 2, Config::kWinH / 2, 
    75, 
    Colors::kProjectionGrey
  );
  
  current_block.draw();
  block_projection.draw();
  player.render();
  for (Enemy* enemy : enemies) {
    enemy->render();
  }

  //DebugRenderRect();

  // DEBUG
  //DrawRectangleRec(Config::kLeftWallRect, BLUE);
  //DrawRectangleRec(Config::kRightWallRect, BLUE);
}

void
Game::update() {
  player.update();
  appendEnemy();

  for (Enemy* enemy : enemies) {
    enemy->update();
  }

  handleInput();

  if (eventTriggered(0.5)) {
    blockMoveDown(current_block);
    updateCurrentBlockRect();

    if (!isBlockOutside(current_block)) {
      player.handleDeath();
      for (Enemy* enemy : enemies) {
        score += enemy->handleDeath();
      }
    }

    // DEBUG:
    std::cout << score << std::endl;
  }

  updateCurrentBlockRect();
  updateProjection();

}

bool
Game::eventTriggered(double tickInterval) {
  double currentTime = GetTime();

  // if the time passed the tick_interval
  if (currentTime - last_update_time >= tickInterval) {
    last_update_time = currentTime;
    return true;
  }

  return false;
}

void
Game::handleInput() {
  int key = GetKeyPressed();

  switch (key) {
    case KEY_J:
      blockMoveLeft(current_block);
      break;
    case KEY_L:
      blockMoveRight(current_block);
      break;
    case KEY_K:
      currentBlockInstantMoveDownAndCheckDeath();
      lockBlock();
      break;
    case KEY_I:
      rotateBlock(current_block);
      break;
  }

  player.handleInput();
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
Game::blockInstateMoveDown(Block& block) {
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
    current_block.move(1, 0);

    updateCurrentBlockRect();

    if (!isBlockOutside(current_block)) {
      player.handleDeath();
      for (Enemy* enemy : enemies) {
        score += enemy->handleDeath();
      }
    }

    if (isBlockOutside(current_block) || isGridOccupied(current_block) == false) {
      current_block.move(-1, 0);
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
  Vector<Position> current_checked_cell = block.getCellPosition();

  for (Position tile : current_checked_cell) {
    if (grid.isGridEmpty(tile.row, tile.col) == false) {
      return false;
    }
  }

  return true;
}
bool
Game::isBlockOutside(Block& block) {
  Vector<Position> current_checked_cell = block.getCellPosition();

  for (Position cell_pos : current_checked_cell) {
    if (grid.isCellOutside(cell_pos.row, cell_pos.col)) {
      return true;
    }
  }

  return false;
}
void
Game::lockBlock() {
  Vector<Position> current_checked_cell = current_block.getCellPosition();

  // Set the grid where the current block located to match the current block
  // color.
  // Also spawn Rectangle for the player to collide.
  updateGridColor(current_checked_cell);
  updateLandedBlockRect(current_checked_cell);

  // Update the block
  current_block = next_block;

  updateCurrentBlockRect();

  // Instantly Move block projection to the ground when created.
  updateProjection();

  // prepare for the next block.
  next_block = pickRandomBlock();

  score += grid.clearFullRow() * Config::kNumOfCols;
}
void
Game::updateGridColor(Vector<Position> cell) {
  for (Position pos : cell) {
    grid.updateGridColor(pos.row, pos.col, current_block.color_id());
  }
}
void
Game::updateLandedBlockRect(Vector<Position> cell) {
  for (Position pos : cell) {
    landed_block_rect.push_back({
      (float)pos.col * Config::kCellSize + Config::kGridOffsetX, 
      (float)pos.row * Config::kCellSize + Config::kGridOffsetY, 
      Config::kCellSize, 
      Config::kCellSize
    });
  }
}


void
Game::createCurrentBlockRect() {
  const Vector<Position>& curr_block_pos = current_block.getCellPosition();
  for (Position pos : curr_block_pos) {
    current_block_rect.push_back(Rectangle {
      (float)pos.col * Config::kCellSize + Config::kGridOffsetX,
      (float)pos.row * Config::kCellSize + Config::kGridOffsetY,
      Config::kCellSize,
      Config::kCellSize,
    });
  }
}
void
Game::clearCurrentBlockRect() {
  current_block_rect.clear();
}
void
Game::updateCurrentBlockRect() {
  clearCurrentBlockRect();
  createCurrentBlockRect();
}

void
Game::updateProjection() {
  block_projection = current_block;
  block_projection.color_id(8);
  blockInstateMoveDown(block_projection);
}

void
Game::debugRenderRect() {
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

