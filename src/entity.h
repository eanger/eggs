#pragma once

#include "position.h"
#include "entity_type.h"

struct SDL_Texture;

namespace eggs {
class World;

class Entity {
  public:
    Entity(EntityType& type, Position position)
      : position_{position}, type_(type) {}
    void update(World& world) {}
    SDL_Texture* get_texture() { return type_.texture_.get(); }
    Position position_;
  private:
    EntityType& type_;
};

}
