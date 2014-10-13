#pragma once

#include <memory>
#include <vector>

#include "entity.h"

namespace {
const unsigned int kWorldWidth = 22;
const unsigned int kWorldHeight = 22;
const unsigned int kPlayerStartLoc = kWorldHeight / 2;
const unsigned int kTotalMoves = 100;
}

namespace eggs {
class World {
  enum class Tile{
    TOKEN,
    PLAYER,
    WALL,
    EMPTY
  };
  enum class State{
    START,
    PLAYING,
    GAME_OVER
  };

  std::array<std::array<Tile, kWorldHeight>, kWorldWidth> map_;
  Entity token_;
  Entity player_;
  Entity wall_;
  Entity empty_;
  State state_;
  unsigned int player_x_, player_y_;
  unsigned int score_;
  unsigned int moves_left_;

  public:
  World();
  bool update(int key_pressed);
  void draw(Screen* screen);
};
}
