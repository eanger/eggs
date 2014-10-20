#pragma once
#include <string>

#include <SFML/Graphics.hpp>

namespace eggs{
struct Icon;
class World;

class Screen{
  private:
    sf::RenderWindow window_;
    sf::RectangleShape token_, player_, wall_;
    sf::Font font_;

  public:
    Screen(unsigned int width, unsigned int height);
    void render(const World& world);
    void draw_icon_at(const Icon& icon, unsigned int y, unsigned int x);
    void print_line_at(const std::string& line, unsigned int y, unsigned int x);
    void print_line_centered(const std::string& line, unsigned int y);
    sf::RenderWindow& get_window();
    void draw();
    void draw_frame_time(float frame_time, const World& world);
};
}
