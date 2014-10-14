#include <iostream>
#include <memory>
#include <random>
#include <sstream>
#include <string>

#include "entity.h"
#include "screen.h"
#include "icon.h"

#include "world.h"

using namespace std;

namespace {
const bool kGameOver = true;
const bool kKeepPlaying = false;
}

namespace eggs {

World::World() : 
    token_{L'.'},
    player_{L'@'},
    wall_{L'#'},
    empty_{L' '},
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

bool World::update(int key_pressed) {
  switch(state_){
    case State::START:
      state_ = State::PLAYING;
      return kKeepPlaying;
    case State::PLAYING:
    {
      int xdiff = 0;
      int ydiff = 0;
      switch(key_pressed){
        case L'w':
          if(player_y_ == 1){ // at top wall
            return kKeepPlaying;
          }
          ydiff = -1;
          break;
        case L's':
          if(player_y_ == kWorldHeight - 2){ // at bottom wall
            return kKeepPlaying;
          }
          ydiff = 1;
          break;
        case L'a':
          if(player_x_ == 1){ // at left wall
            return kKeepPlaying;
          }
          xdiff = -1;
          break;
        case L'd':
          if(player_x_ == kWorldWidth - 2){ // at right wall
            return kKeepPlaying;
          }
          xdiff = 1;
          break;
        case L'q':
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
  }
}

void World::draw(Screen* screen){
  for(unsigned int row = 0; row < kWorldHeight; ++row){
    for(unsigned int col = 0; col < kWorldWidth; ++col){
      Icon icon;
      switch(map_[row][col]){
        case Tile::TOKEN:
          icon = token_.icon_;
          break;
        case Tile::PLAYER:
          icon = player_.icon_;
          break;
        case Tile::WALL:
          icon = wall_.icon_;
          break;
        case Tile::EMPTY:
          icon = empty_.icon_;
          break;
      }
      screen->draw_icon_at(icon, row, col);
    }
  }
  stringstream score_str, moves_str;
  score_str << "Score: " << score_;
  screen->print_line_centered(score_str.str(), kWorldHeight);
  moves_str << "Moves Left: " << moves_left_;
  screen->print_line_centered(moves_str.str(), kWorldHeight + 1 /* below score */);
}

}

