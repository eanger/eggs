#include <iostream>
#include <memory>
#include <random>
#include <sstream>
#include <string>

#include "icon.h"
#include "input.h"

#include "world.h"

using namespace std;

namespace {
const bool kGameOver = true;
const bool kKeepPlaying = false;
}

namespace eggs {

World::World() : 
    state_{State::START},
    player_x_{kPlayerStartLoc},
    player_y_{kPlayerStartLoc},
    score_{0},
    moves_left_{kTotalMoves} {
  random_device rd;
  default_random_engine eng(rd());
  uniform_int_distribution<int> dist(0,1);
  for(unsigned int i = 0; i < kWorldWidth; ++i){
    for(unsigned int j = 0; j < kWorldHeight; ++j){
      if(i == 0 || i == kWorldHeight - 1 ||
         j == 0 || j == kWorldWidth - 1){
        map_[j][i] = Tile::WALL;
      } else if(dist(eng)){
        map_[j][i] = Tile::TOKEN;
      } else {
        map_[j][i] = Tile::EMPTY;
      }
    }
  }
  map_[kPlayerStartLoc][kPlayerStartLoc] = Tile::PLAYER;
}

bool World::update(InputAction action) {
  switch(state_){
    case State::START:
      state_ = State::PLAYING;
      return kKeepPlaying;
    case State::PLAYING:
    {
      int xdiff = 0;
      int ydiff = 0;
      switch(action){
        case InputAction::UP:
          if(player_y_ == 1){ // at top wall
            return kKeepPlaying;
          }
          ydiff = -1;
          break;
        case InputAction::DOWN:
          if(player_y_ == kWorldHeight - 2){ // at bottom wall
            return kKeepPlaying;
          }
          ydiff = 1;
          break;
        case InputAction::LEFT:
          if(player_x_ == 1){ // at left wall
            return kKeepPlaying;
          }
          xdiff = -1;
          break;
        case InputAction::RIGHT:
          if(player_x_ == kWorldWidth - 2){ // at right wall
            return kKeepPlaying;
          }
          xdiff = 1;
          break;
        case InputAction::QUIT:
          state_ = State::GAME_OVER;
        default:
          return kKeepPlaying;
      }
      --moves_left_;
      auto new_x = player_x_ + xdiff;
      auto new_y = player_y_ + ydiff;
      if(map_[new_y][new_x] == Tile::TOKEN){
        ++score_;
      }
      map_[new_y][new_x] = Tile::PLAYER;
      map_[player_y_][player_x_] = Tile::EMPTY;
      player_x_ = new_x;
      player_y_ = new_y;
      if(moves_left_ == 0){
        state_ = State::GAME_OVER;
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

