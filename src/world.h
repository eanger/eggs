#pragma once

#include <vector>

namespace eggs {

const unsigned int kWorldWidth = 22;
const unsigned int kWorldHeight = 22;
const unsigned int kPlayerStartLoc = kWorldHeight / 2;

class Input;
class World {
  public:
  enum class Tile{
    TOKEN,
    PLAYER,
    WALL
  };
  enum class State{
    START,
    PLAYING,
    GAME_OVER
  };

  using position_t = std::pair<unsigned int, unsigned int>;
  std::vector<position_t> entity_positions_;
  std::vector<Tile> entity_types_;
  State state_;

  World();
  bool update(const Input& input);
};
}
