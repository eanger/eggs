#include <iostream>
#include <memory>
#include <random>
#include <sstream>
#include <string>

#include "input.h"
#include "timer.h"

#include "world.h"

using namespace std;

namespace eggs {

World::World() : state_{State::START}, is_debug_{true} {
  random_device rd;
  default_random_engine eng(rd());
  uniform_int_distribution<int> dist(0,2);
  for(unsigned int i = 0; i < kWorldWidth; ++i){
    for(unsigned int j = 0; j < kWorldHeight; ++j){
      if(i == 0 || i == kWorldHeight - 1 ||
         j == 0 || j == kWorldWidth - 1){
        entity_positions_.emplace_back(i, j);
        entity_types_.emplace_back(Tile::WALL);
      }
    }
  }
}

void World::update(const Input& input) {
  timer_.reset();
  timer_.start();
  switch(state_){
    case State::START:
      state_ = State::PLAYING;
      break;
    case State::PLAYING:
      switch(input.action){
        case Input::Action::QUIT:
          state_ = State::GAME_OVER;
          break;
        case Input::Action::MOUSE_BUTTON_DOWN:
          break;
        case Input::Action::DEBUG:
          is_debug_ = !is_debug_; // toggle debug state
        default:
          break;
      }
      break;
    default:
      throw runtime_error("Invalid game state");
  }
  timer_.stop();
}

}

