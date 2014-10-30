#pragma once

#include <vector>

namespace eggs {

const unsigned int kWorldWidth = 22;
const unsigned int kWorldHeight = 22;
const unsigned int kPlayerStartLoc = kWorldHeight / 2;
const int kTileSize = 20;
const unsigned int kExtraScreenWidth = 200;
const unsigned int kExtraScreenHeight = 50;

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
  bool is_debug_;

  World();
  void update(const Input& input);
};
}
