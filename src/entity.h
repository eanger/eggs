#pragma once
#define _XOPEN_SOURCE_EXTENDED
#include <ncursesw/ncurses.h>

namespace eggs {
struct Screen;
class Entity {
  cchar_t icon_;

  public:
  unsigned int y_, x_;
  Entity(unsigned int y, unsigned int x, wchar_t icon_char);
  void update();
  void draw(Screen* screen);
};
}
