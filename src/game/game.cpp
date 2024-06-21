#include <algorithm>
#include <raylib.h>
#include <vector>
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
  , is_game_over {false}
  , is_game_started {false}
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
  , game_event_publisher_ {}
  , subscriber_ {}
{
  createCurrentBlockRect();
  updateProjection();

  subscriber_
    .addNotifyCallback("OnEnemyDeath", [this](){
      score += 2;

      for (Enemy* enemy : enemies) {
        if (enemy->marked_for_delete) {
          game_event_publisher_.removeSubscriber(enemy->subscriber());
          enemies.erase(
            std::remove(
                enemies.begin(),
                enemies.end(),
                enemy
            ),
            enemies.end()
          );
          delete enemy;
        }
      }
    })
    ->addNotifyCallback("OnPlayerDeath", [this](){
      handleGameOver();
    });

  // NOTE: enemy subscriber are assigned on the spawner function.
  game_event_publisher_
    .addSubscriber(player.subscriber());
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
  const int maxX = config::kNumOfCols * config::kCellSize;
  const int randX = (rand() % maxX) + config::kGridOffsetX;

  // DEBUG:
  std::cout << "Enemy spawned!" << std::endl; 

  Enemy* new_enemy = new Enemy(this, randX);
  game_event_publisher_.addSubscriber(new_enemy->subscriber());

  return new_enemy;
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


  //
  if (!is_game_started) {
    DrawText(
      "Press SPACE to Start", 
      config::kWinW / 4 , config::kWinH / 2 + 75, 
      75, 
      Colors::kProjectionGrey
    );

  }
  
  // score
  //if (is_game_started) {
    DrawText(
      std::to_string(score).c_str(), 
      config::kWinW / 2, config::kWinH / 2, 
      75, 
      Colors::kProjectionGrey
    );
  //}
    

  if (!is_game_over && is_game_started) {
    current_block.draw();
    block_projection.draw();
    for (Enemy* enemy : enemies) {
      enemy->render();
    }
  }
  else if (is_game_over && !is_game_started) {
    DrawText(
      "GAME OVER", 
      config::kWinW * 3 / 8 , config::kWinH / 2 - 75, 
      75, 
      Colors::kProjectionGrey
    );
  }

  player.render();

  //debugRenderRect();

  // DEBUG
  //DrawRectangleRec(config::kLeftWallRect, BLUE);
  //DrawRectangleRec(config::kRightWallRect, BLUE);
  //DrawRectangleRec(config::kGroundRect, BLUE);
}

void
Game::update() {
  player.update();
  handleInput();

  if (!is_game_over) {
    appendEnemy();

    for (Enemy* enemy : enemies) {
      enemy->update();
    }

    if (eventTriggered(0.5)) {
      blockMoveDown(current_block);
      updateCurrentBlockRect();
    }
  }
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
      if (is_game_started) {
        blockMoveLeft(current_block);
        updateCurrentBlockRect();
        updateProjection();
      }
      break;
    case KEY_L:
      if (is_game_started) {
        blockMoveRight(current_block);
        updateCurrentBlockRect();
        updateProjection();
      }
      break;
    case KEY_K:
      if (is_game_started) {
        currentBlockInstantMoveDownAndCheckDeath();
        lockBlock();
      }
      break;
    case KEY_I:
      if (is_game_started) {
        rotateBlock(current_block);
        updateCurrentBlockRect();
        updateProjection();
      }
      break;
    case KEY_SPACE:
      if (is_game_started == false) {
        onGameRestart();
      }
  }

  //player.handleInput();
}



void
Game::blockMoveLeft(Block& block) {
  block.move(0, -1);

  if (!isBlockOutside(current_block)) {
    game_event_publisher_.notifySubscriber("OnBlockMove");
  }

  // if block out of bound to the left, Move the block 1 cell to the right.
  if (isBlockOutside(block) || isGridOccupied(block) == false) {
    block.move(0, 1);
  }
}
void
Game::blockMoveRight(Block& block) {
  block.move(0, 1);

  if (!isBlockOutside(current_block)) {
    game_event_publisher_.notifySubscriber("OnBlockMove");
  }

  if (isBlockOutside(block) || isGridOccupied(block) == false) {
    block.move(0, -1);
  }
}
void
Game::blockMoveDown(Block& block) {
  block.move(1, 0);

  if (!isBlockOutside(current_block)) {
    game_event_publisher_.notifySubscriber("OnBlockMove");
  }

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


    if (isBlockOutside(current_block) || isGridOccupied(current_block) == false) {
      current_block.move(-1, 0);
      break;
    }

    updateCurrentBlockRect();

    if (!isBlockOutside(current_block)) {
      game_event_publisher_.notifySubscriber("OnBlockMove");
    }
  }
}



void
Game::rotateBlock(Block& block) {
  block.rotate();

  if (!isBlockOutside(current_block)) {
    game_event_publisher_.notifySubscriber("OnBlockMove");
  }

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
  // DEBUG
  game_event_publisher_.notifySubscriber("OnBlockLock");

  Vector<Position> current_checked_cell = current_block.getCellPosition();

  // Set the grid where the current block located to match the current block
  // color.
  // Also spawn Rectangle for the player to collide.
  checkIfStackFull(&current_checked_cell);
  updateGridColor(&current_checked_cell);
  updateLandedBlockRect(&current_checked_cell);

  // Update the block
  current_block = next_block;

  updateCurrentBlockRect();

  // Instantly Move block projection to the ground when created.
  updateProjection();

  // prepare for the next block.
  next_block = pickRandomBlock();

  score += (int)(grid.clearFullRow() * config::kNumOfCols / 2.f);
}
void
Game::updateGridColor(Vector<Position>* cell) {
  for (Position pos : *cell) {
    grid.updateGridColor(pos.row, pos.col, current_block.color_id());
  }
}
void
Game::updateLandedBlockRect(Vector<Position>* cell) {
  for (Position pos : *cell) {
    landed_block_rect.push_back({
      (float)pos.col * config::kCellSize + config::kGridOffsetX, 
      (float)pos.row * config::kCellSize + config::kGridOffsetY, 
      config::kCellSize, 
      config::kCellSize
    });
  }
}
void
Game::checkIfStackFull(Vector<Position>* cell) {
  for (Position pos : *cell) {
    if (pos.row <= 0) {
      std::cout << "Stack is full" << std::endl;
      game_event_publisher_.notifySubscriber("OnStackFull");
      handleGameOver();
      return;
    }
  }
}

void
Game::createCurrentBlockRect() {
  const Vector<Position>& curr_block_pos = current_block.getCellPosition();
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

void
Game::handleGameOver() {
  current_block.color_id(0); // temporary fix to make the current block invisible.
  is_game_over = true;
  is_game_started = false;
  grid.resetColor();
}

void
Game::onGameRestart() {
  score = 0;

  current_block = next_block;
  next_block = pickRandomBlock();
  createCurrentBlockRect();
  updateProjection();

  for (Enemy* enemy : enemies) {
    game_event_publisher_.removeSubscriber(enemy->subscriber());
    delete enemy;
  }
  enemies.clear();

  is_game_over = false;
  is_game_started = true;

  current_block_rect.clear();
  landed_block_rect.clear();

  game_event_publisher_.notifySubscriber("OnGameRestart");
}
