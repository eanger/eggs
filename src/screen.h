#pragma once
#include <string>
#ifndef _XOPEN_SOURCE_EXTENDED
#define _XOPEN_SOURCE_EXTENDED
#endif
#include <ncursesw/ncurses.h>

namespace eggs{
struct Screen{
  Screen();
  ~Screen();
  void update();
  void draw_char_at(const cchar_t& icon, unsigned int y, unsigned int x);
  void print_line_at(const std::string& line, unsigned int y, unsigned int x);
  void clear();
};
}
