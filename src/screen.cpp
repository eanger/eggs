#include <clocale>
#include <stdexcept>
#include <sstream>
#include <iostream>
#include <string>

#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_image.h"

#include "world.h"
#include "timer.h"
#include "input.h"

#include "screen.h"

using namespace std;

namespace {
const int kFontPtSize = 16;
const int kFontHeight = 20;
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

Screen::Screen() :
  assets_path_{SDL_GetBasePath()},
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
                         kStartWidth,
                         kStartHeight,
                         SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE)},
  renderer_{make_resource(SDL_CreateRenderer,
                          SDL_DestroyRenderer,
                          window_.get(),
                          -1 /* first available driver */,
                          SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)},
  font_{make_resource(TTF_OpenFont, TTF_CloseFont,
                      (assets_path_ + "../assets/DroidSansMono.ttf").c_str(),
                      kFontPtSize)},
  token_{make_resource(make_texture_resource,
                       SDL_DestroyTexture,
                       renderer_.get(),
                       (assets_path_ +  "/../assets/chair.bmp").c_str())},
  player_{make_resource(make_texture_resource,
                       SDL_DestroyTexture,
                       renderer_.get(),
                       (assets_path_ +  "/../assets/guy.bmp").c_str())},
  wall_{make_resource(make_texture_resource,
                       SDL_DestroyTexture,
                       renderer_.get(),
                       (assets_path_ +  "/../assets/door.bmp").c_str())}
{
	empty_.r = 255;
	empty_.g = 255;
	empty_.b = 255;
	empty_.a = 0;
	text_color_.r = 0;
	text_color_.g = 0;
	text_color_.b = 0;
	text_color_.a = 0;
}

void Screen::update(const Input& input, const World& world){
  SDL_SetRenderDrawColor(renderer_.get(), empty_.r, empty_.g, empty_.b, empty_.a);
  SDL_RenderClear(renderer_.get());
  // Do the actual rendering of world contents
  for (unsigned int entity_id = 0; entity_id < world.entity_positions_.size();
       ++entity_id) {
    const auto& entity_type = world.entity_types_[entity_id];
    // Get entity position in camera coordinates
    auto entity_pos =
        world_to_camera(world.entity_positions_[entity_id], world.camera_);
    SDL_Texture* texture{nullptr};
    switch(entity_type){
      case World::Tile::TOKEN:
        texture = token_.get();
        break;
      case World::Tile::PLAYER:
        texture = player_.get();
        break;
      case World::Tile::WALL:
        texture = wall_.get();
        break;
    }
    SDL_Rect rect{(int)entity_pos.x, (int)entity_pos.y, kTileSize, kTileSize};
    SDL_RenderCopy(renderer_.get(), texture, nullptr, &rect);
  }
  if(world.is_debug_){
    auto world_time = world.timer_.read_ms();
    draw_frame_time(world_time, world);
    stringstream mousestr;
    mousestr << "Mouse: (" << world.mouse_pos.x << "," << world.mouse_pos.y << ")";
    print_line_at(mousestr.str(), kStartHeight - kFontHeight, 0);
  }
  SDL_RenderPresent(renderer_.get());
}

void Screen::draw_frame_time(float frame_time, const World& world){
  stringstream frame_time_str;
  frame_time_str.precision(2);
  frame_time_str << "Frame time: " << frame_time << "ms";
  print_line_at(frame_time_str.str(), 0, 0);
}

}
