#pragma once
#include <string>

#include "SDL.h"
#include "SDL_ttf.h"

#include "sdl_helpers.h"

namespace eggs{
class World;

class Screen{
  private:
    ScopedCallHandle sdl_init_, ttf_init_;
    ResourceHandle<SDL_Window> window_;
    ResourceHandle<SDL_Renderer> renderer_;
    ResourceHandle<TTF_Font> font_;

    SDL_Color token_, player_, wall_, empty_, text_color_;

  public:
    Screen(unsigned int width, unsigned int height);
    void render(const World& world);
    void print_line_at(const std::string& line, unsigned int y, unsigned int x);
    void draw();
    void draw_frame_time(float frame_time, const World& world);
};
}
