#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <raylib.h>

#include "Components.hpp"


class Game;

class Player {
private:
  RectCollider collider_;
  RectRender renderer_;
  TransformComponent transform_;

  bool is_alive_;

  const Game* game_;

public: // ctor, dtor, get, set
  Player(const Game* game);
  Rectangle rect();

public:
  void update();
  void render();

  void handleInput();

  void handleDeath();

private:

};

#endif // PLAYER_HPP
