#include <clocale>
#include <stdexcept>
#include <sstream>
#include <iostream>

#include "SDL.h"

#include "icon.h"
#include "world.h"

#include "screen.h"

using namespace std;

namespace {
const unsigned int kTileSize = 10;
}

namespace eggs{

void Screen::print_line_at(const std::string& line,
                           unsigned int y,
                           unsigned int x) {
  /*
  sf::Text text{line, font_};
  text.setPosition(x, y);
  window_.draw(text);
  */
}

void Screen::print_line_centered(const std::string& line, unsigned int y) {
  /*
  sf::Text text{line, font_};
  auto bounds = text.getGlobalBounds();
  auto size = window_.getSize();
  print_line_at(line, (size.x - bounds.width) / 2, y);
  */
}

Screen::Screen(unsigned int width, unsigned int height) :
  token_{255, 255, 255, 0} /* white */,
  player_{255, 0, 0, 0} /* red */,
  wall_{0, 255, 255, 0} /* cyan */,
  empty_{0, 0, 0, 0} /* black */
{
  if(SDL_Init(SDL_INIT_EVERYTHING) != 0){
    throw runtime_error("Unable to init SDL2");
  }

  window_ = SDL_CreateWindow("EGGS",
                             SDL_WINDOWPOS_UNDEFINED,
                             SDL_WINDOWPOS_UNDEFINED,
                             width,
                             height,
                             0 /* no flags */);
  if(window_ == nullptr){
    throw runtime_error("Unable to make a window");
  }

  renderer_ = SDL_CreateRenderer(window_,
                                 -1 /* first available render driver */,
                                 SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if(renderer_ == nullptr){
    throw runtime_error("Unable to make a renderer");
  }
	/*string font_fname{BINDIR "/../assets/Sail-Regular.otf"};
  if(!font_.loadFromFile(font_fname)){
    throw std::runtime_error("Unable to load font");
  }
  */
}

void Screen::render(const World& world){
  SDL_SetRenderDrawColor(renderer_, empty_.r, empty_.g, empty_.b, empty_.a);
  SDL_RenderClear(renderer_);
  // Do the actual rendering of world contents
  unsigned int start_x = 0, start_y = 0;
  for(const auto& row : world.map_){
    for(const auto& tile : row){
      SDL_Color* color{nullptr};
      switch(tile){
        case World::Tile::TOKEN:
          color = &token_;
          break;
        case World::Tile::PLAYER:
          color = &player_;
          break;
        case World::Tile::WALL:
          color = &wall_;
          break;
        case World::Tile::EMPTY:
          color = &empty_;
          break;
      }
      if(color){
        SDL_Rect rect{start_x, start_y, kTileSize, kTileSize};
        SDL_SetRenderDrawColor(renderer_, color->r, color->g, color->b, color->a);
        SDL_RenderFillRect(renderer_, &rect);
        /*
        auto surf = SDL_GetWindowSurface(window_);
        SDL_FillRect(surf, &rect, SDL_MapRGB(surf->format, 
                                             color->r,
                                             color->g,
                                             color->b));
        auto tex = SDL_CreateTextureFromSurface(renderer_, surf);
        SDL_RenderCopy(renderer_, tex, nullptr, nullptr);
        SDL_FreeSurface(surf);
        SDL_DestroyTexture(tex);
        */
      }
      start_x += kTileSize;
    }
    start_y += kTileSize;
    start_x = 0;
  }
  stringstream score_str;
  score_str << "Score: " 
            << world.score_ 
            << "\nMoves Left: " 
            << world.moves_left_;
  print_line_at(score_str.str(), kTileSize * world.map_.size(), 0);
}

void Screen::draw() {
  SDL_RenderPresent(renderer_);
}

void Screen::draw_icon_at(const Icon& icon, unsigned int y, unsigned int x){
}

void Screen::draw_frame_time(float frame_time, const World& world){
  stringstream frame_time_str;
  frame_time_str << "Frame time: " << frame_time << "ms";
  print_line_at(frame_time_str.str(), 0, kTileSize * world.map_.size());
}

}
