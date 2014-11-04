#pragma once

#include "utils/glm/glm.hpp"

namespace eggs {
class World;
class Entity {
  public:
    enum class Tile{
      CHAIR,
      DESK,
      DOOR,
      WORKER,
      WALL
    } type_;

    Entity(Entity::Tile type, glm::vec2 position)
      : type_{type}, position_{position} {}
    void update(World& world) {}
    glm::vec2 position_;
};

}
