#include <iostream>
#include <memory>

#include "entity.h"

#include "world.h"

using namespace std;

namespace eggs {

struct Screen;

void World::update() {
  for(auto& entity : entities_){
    entity->update();
  }
}

void World::draw(Screen* screen){
  for(const auto& entity : entities_){
    entity->draw(screen);
  }
}

void World::add_entity(unsigned int y, unsigned int x, wchar_t icon_char){
  auto entity = std::unique_ptr<Entity>(new Entity(y, x, icon_char));
  entities_.push_back(std::move(entity));
}

}

