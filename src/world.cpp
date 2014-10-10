#include <iostream>
#include <memory>
#include <random>

#include "entity.h"

#include "world.h"

using namespace std;

namespace {
const unsigned int kWorldWidth = 20;
const unsigned int kWorldHeight = 20;
}

namespace eggs {

struct Screen;

World::World() {
  random_device rd;
  default_random_engine eng(rd());
  uniform_int_distribution<int> dist(0,1);
  for(unsigned int i = 0; i < kWorldWidth; ++i){
    for(unsigned int j = 0; j < kWorldHeight; ++j){
      if(dist(eng)){
        add_entity(j, i, L'@');
      }
    }
  }
}

void World::update(int key_pressed) {
  if(key_pressed == L'd'){
    const auto& last = entities_.back();
    mvdelch(last->y_, last->x_);
    entities_.pop_back();
  }
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

