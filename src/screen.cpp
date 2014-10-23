#include <clocale>
#include <stdexcept>
#include <sstream>
#include <iostream>

#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_image.h"

#include "world.h"

#include "screen.h"

using namespace std;

namespace {
const int kTileSize = 20;
const int kFontPtSize = 24;
const char* kFontPath = BINDIR "/../assets/Sail-Regular.otf";
}

namespace eggs{

void Screen::print_line_at(const std::string& line,
                           unsigned int y,
                           unsigned int x) {
  auto surf = TTF_RenderUTF8_Shaded(font_.get(), line.c_str(), text_color_, empty_);
  SDL_Rect position{(int) x, (int) y, surf->w, surf->h};
  auto texture = SDL_CreateTextureFromSurface(renderer_.get(), surf);
  SDL_RenderCopy(renderer_.get(), texture, nullptr /* whole text texture */, &position);
  SDL_DestroyTexture(texture);
  SDL_FreeSurface(surf);
}

SDL_Texture* make_texture_resource(SDL_Renderer* renderer, const char* filename){
  auto surf = make_resource(IMG_Load, SDL_FreeSurface, filename);
  return SDL_CreateTextureFromSurface(renderer, surf.get());
}

Screen::Screen(unsigned int width, unsigned int height) :
  sdl_init_{make_scoped_call(SDL_Init,
                             SDL_Quit,
                             SDL_INIT_TIMER |
                             SDL_INIT_AUDIO |
                             SDL_INIT_VIDEO |
                             SDL_INIT_EVENTS)},
  ttf_init_{make_scoped_call(TTF_Init, TTF_Quit)},
  img_init_{make_scoped_call(IMG_Init, IMG_Quit, 0 /* no special libraries */)},
  window_{make_resource(SDL_CreateWindow,
                         SDL_DestroyWindow,
                         "EGGS",
                         SDL_WINDOWPOS_UNDEFINED,
                         SDL_WINDOWPOS_UNDEFINED,
                         width,
                         height,
                         0)},
  renderer_{make_resource(SDL_CreateRenderer,
                          SDL_DestroyRenderer,
                          window_.get(),
                          -1 /* first available driver */,
                          SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)},
  font_{make_resource(TTF_OpenFont, TTF_CloseFont, kFontPath, kFontPtSize)},
  token_{make_resource(make_texture_resource,
                       SDL_DestroyTexture,
                       renderer_.get(),
                       BINDIR "/../assets/chair.bmp")},
  player_{make_resource(make_texture_resource,
                       SDL_DestroyTexture,
                       renderer_.get(),
                       BINDIR "/../assets/guy.bmp")},
  wall_{make_resource(make_texture_resource,
                       SDL_DestroyTexture,
                       renderer_.get(),
                       BINDIR "/../assets/door.bmp")},
  empty_{255, 255, 255, 0} /* white */,
  text_color_{0, 0, 0, 0} /* black */
{}

void Screen::render(const World& world){
  SDL_SetRenderDrawColor(renderer_.get(), empty_.r, empty_.g, empty_.b, empty_.a);
  SDL_RenderClear(renderer_.get());
  // Do the actual rendering of world contents
  int start_x = 0, start_y = 0;
  for(const auto& row : world.map_){
    for(const auto& tile : row){
      SDL_Texture* texture{nullptr};
      switch(tile){
        case World::Tile::TOKEN:
          texture = token_.get();
          break;
        case World::Tile::PLAYER:
          texture = player_.get();
          break;
        case World::Tile::WALL:
          texture = wall_.get();
          break;
        default:
          break;
      }
      SDL_Rect rect{start_x, start_y, kTileSize, kTileSize};
      if(texture){
        SDL_RenderCopy(renderer_.get(), texture, nullptr, &rect);
      } else {
        SDL_SetRenderDrawColor(renderer_.get(), empty_.r, empty_.g, empty_.b, empty_.a);
        SDL_RenderFillRect(renderer_.get(), &rect);
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
  SDL_RenderPresent(renderer_.get());
}

void Screen::draw_frame_time(float frame_time, const World& world){
  stringstream frame_time_str;
  frame_time_str << "Frame time: " << frame_time << "ms";
  print_line_at(frame_time_str.str(), 0, kTileSize * world.map_.size());
}

}
