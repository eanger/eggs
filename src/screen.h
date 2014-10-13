#pragma once
#include <string>

namespace eggs{
struct Icon;
struct Screen{
  Screen();
  ~Screen();
  void update();
  void draw_icon_at(const Icon& icon, unsigned int y, unsigned int x);
  void print_line_at(const std::string& line, unsigned int y, unsigned int x);
  void print_line_centered(const std::string& line, unsigned int y);
  void clear();
};
}
