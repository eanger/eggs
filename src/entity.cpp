#define _XOPEN_SOURCE_EXTENDED
#include <ncursesw/ncurses.h>

#include "screen.h"

#include "entity.h"

namespace eggs {

Entity::Entity(uint x, uint y, wchar_t icon_char){
  setcchar(&icon_,
           &icon_char,
           0/* default attrs */,
           0 /* default color */,
           nullptr);
}

void Entity::update() {
}

void Entity::draw(Screen* screen){
  screen->draw_char_at(icon_, y_, x_);
}

}

