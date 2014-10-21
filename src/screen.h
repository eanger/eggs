#pragma once
#include <string>

#include "SDL.h"

struct SDL_Window;
struct SDL_Renderer;

namespace eggs{
struct Icon;
class World;

class Screen{
  private:
    SDL_Window*  window_;
    SDL_Renderer* renderer_;
    SDL_Color token_, player_, wall_, empty_;
    //sf::Font font_;

  public:
    Screen(unsigned int width, unsigned int height);
    void render(const World& world);
    void print_line_at(const std::string& line, unsigned int y, unsigned int x);
    void print_line_centered(const std::string& line, unsigned int y);
    void draw();
    void draw_frame_time(float frame_time, const World& world);
};
}
