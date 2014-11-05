#pragma once

#include "position.h"

namespace eggs {
class World;

enum class Tile{
  CHAIR,
  DESK,
  DOOR,
  WORKER,
  WALL
};

class Entity {
  public:
    Tile type_;

    Entity(Tile type, Position position)
      : type_{type}, position_{position} {}
    void update(World& world) {}
    Position position_;
};

}
