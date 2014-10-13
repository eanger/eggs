#pragma once
#ifndef _XOPEN_SOURCE_EXTENDED
#define _XOPEN_SOURCE_EXTENDED
#endif
#include <ncursesw/ncurses.h>

namespace eggs {
struct Screen;
struct Entity {
  cchar_t icon_;
  Entity(wchar_t icon_char);
};
}
