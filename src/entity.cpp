#ifndef _XOPEN_SOURCE_EXTENDED
#define _XOPEN_SOURCE_EXTENDED
#endif
#include <ncursesw/ncurses.h>

#include "screen.h"

#include "entity.h"

namespace eggs {

Entity::Entity(wchar_t icon_char) {
  setcchar(&icon_,
           &icon_char,
           0/* default attrs */,
           0 /* default color */,
           nullptr);
}

}

