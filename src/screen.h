#pragma once
#include <string>

#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_image.h"

#include "sdl_helpers.h"
#include "state.h"

namespace eggs{

class Screen{
  private:
    ScopedCallHandle sdl_init_, ttf_init_, img_init_;
    ResourceHandle<SDL_Window> window_;
    ResourceHandle<SDL_Renderer> renderer_;
    ResourceHandle<TTF_Font> font_;

    SDL_Color empty_, text_color_;

  public:
    Screen();
    void update(const State& state);
    void print_line_at(const std::string& line, unsigned int y, unsigned int x);
    void draw_frame_time(float frame_time);
    SDL_Renderer* get_renderer() const { return renderer_.get(); }
};
}
