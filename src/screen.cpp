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
#include "entity.h"
#include "sdl_helpers.h"

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
                      kFontPtSize)}
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
  auto cam_pos = world.camera_.get_position();
  auto bottom_right = camera_to_world(Position{kStartWidth, kStartHeight},
                                      world.camera_);
  for(unsigned int col = cam_pos.y_; col < bottom_right.y_; ++col){
    for(unsigned int row = cam_pos.x_; row < bottom_right.x_; ++row){
    // Get entity position in camera coordinates
      auto entity_world_pos = Position{row, col};
      auto entity_cam_pos = world_to_camera(entity_world_pos, world.camera_);
      if(!world.map_[entity_world_pos]){ /* there's nothing here */
        continue;
      }
      auto texture = world.map_[entity_world_pos]->get_texture();
      SDL_Rect rect{(int)entity_cam_pos.x_, (int)entity_cam_pos.y_, kTileSize,
                    kTileSize};
      SDL_RenderCopy(renderer_.get(), texture, nullptr, &rect);
    }
  }
  if(world.is_debug_){
    auto world_time = world.timer_.read_ms();
    draw_frame_time(world_time, world);
    stringstream mousestr;
    mousestr << "Mouse: (" << world.mouse_pos.x_ << "," << world.mouse_pos.y_ << ")";
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
