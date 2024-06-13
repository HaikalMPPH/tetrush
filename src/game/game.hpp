#ifndef GAME_HPP
#define GAME_HPP

#include <raylib.h>

#include "../engine/utils/typedefs.hpp"
#include "enemy.hpp"
#include "position.hpp"
#include "grid.hpp"
#include "block.hpp"
#include "player.hpp"

class Game {
public:
  Game();
  ~Game();

public:
  Block pickRandomBlock();

  Vector<Block> createTetrominos();
  Enemy* createEnemy();
  void appendEnemy();

  void render();
  void update();
  // * Trigger an event every certain tick (this is for moving the tetraminos down automatically).
  // * tick_interval: how many seconds before the event is triggered.
  bool eventTriggered(double tickInterval);

  void handleInput();


  void blockMoveLeft(Block& block);
  void blockMoveRight(Block& block);
  void blockMoveDown(Block& block);
  void blockInstateMoveDown(Block& block);
  void currentBlockInstantMoveDownAndCheckDeath();
  void rotateBlock(Block& block);

  // Check if the grid next to/below the block is occupied.
  bool isGridOccupied(Block& block);
  bool isBlockOutside(Block& block);

  // Called when the block reaches the ground.
  // Also processed if player/enemy is "squashable"
  void lockBlock();
  void updateGridColor(Vector<Position>* cell);
  void updateLandedBlockRect(Vector<Position>* cell);
  void checkIfStackFull(Vector<Position>* cell);

  void createCurrentBlockRect();
  void clearCurrentBlockRect();
  void updateCurrentBlockRect();   // empty and recreate current_block_rect


  //
  void updateProjection();

  // DEBUG: render tetromino collider.
  void debugRenderRect();
  
  void handleGameOver();

public:
  Grid grid;
  int score;
  bool is_game_over;

  // list of the available tetraminos.
  Vector<Block> block;
  Block current_block;
  Block next_block;

  // Tetramino projection.
  Block block_projection;

  double last_update_time;
  const float enemy_spawn_cooldown;
  float current_enemy_spawn_cooldown;

  // Game entities
  Player player;

  // Enemy are created on the fly
  Vector<Enemy*> enemies;

  // Vector of rect that the position is matched with the color grid.
  // The rect is used for the player collision
  Vector<Rectangle> landed_block_rect;     // collider of a block that are on the ground.
  Vector<Rectangle> current_block_rect;    // collider of the current falling block.
  EventPublisher game_event_publisher_;
  EventSubscriber subscriber_;
};

#endif // GAME_HPP
