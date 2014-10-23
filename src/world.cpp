#include <iostream>
#include <memory>
#include <random>
#include <sstream>
#include <string>

#include "input.h"

#include "world.h"

using namespace std;

namespace {
const bool kGameOver = true;
const bool kKeepPlaying = false;
}

namespace eggs {

World::World() : state_{State::START} {
  random_device rd;
  default_random_engine eng(rd());
  uniform_int_distribution<int> dist(0,2);
  for(unsigned int i = 0; i < kWorldWidth; ++i){
    for(unsigned int j = 0; j < kWorldHeight; ++j){
      if(i == 0 || i == kWorldHeight - 1 ||
         j == 0 || j == kWorldWidth - 1){
        entity_positions_.emplace_back(i, j);
        entity_types_.emplace_back(Tile::WALL);
      } else switch(dist(eng)){
        case 0:
          entity_positions_.emplace_back(i, j);
          entity_types_.emplace_back(Tile::TOKEN);
          break;
        case 1:
          entity_positions_.emplace_back(i, j);
          entity_types_.emplace_back(Tile::PLAYER);
          break;
        default:
          break;
      }
    }
  }
}

bool World::update(const Input& input) {
  switch(state_){
    case State::START:
      state_ = State::PLAYING;
      return kKeepPlaying;
    case State::PLAYING:
    {
      switch(input.action){
        case Input::Action::QUIT:
          state_ = State::GAME_OVER;
        default:
          return kKeepPlaying;
      }
      return kKeepPlaying;
    }
    case State::GAME_OVER:
      return kGameOver;
    default:
      throw runtime_error("Invalid game state");
  }
}

}

