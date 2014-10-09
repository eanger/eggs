#pragma once
#define _XOPEN_SOURCE_EXTENDED
#include <ncursesw/ncurses.h>

namespace eggs {
struct Screen;
class Entity {
  uint x_, y_;
  cchar_t icon_;

  public:
  Entity(uint x, uint y, wchar_t icon_char);
  void update();
  void draw(Screen* screen);
};
}
