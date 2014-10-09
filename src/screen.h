#pragma once
#define _XOPEN_SOURCE_EXTENDED
#include <ncursesw/ncurses.h>

namespace eggs{
struct Screen{
  Screen();
  ~Screen();
  void update();
  void draw_char_at(const cchar_t& icon, unsigned int y, unsigned int x);
};
}
