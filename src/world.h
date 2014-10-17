#pragma once

#include <array>

namespace {
const unsigned int kWorldWidth = 22;
const unsigned int kWorldHeight = 22;
const unsigned int kPlayerStartLoc = kWorldHeight / 2;
const unsigned int kTotalMoves = 100;
}

namespace eggs {
enum class InputAction;
class World {
  public:
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
  State state_;
  unsigned int player_x_, player_y_;
  unsigned int score_;
  unsigned int moves_left_;

  World();
  bool update(InputAction action);
};
}
