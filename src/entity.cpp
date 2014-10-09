#define _XOPEN_SOURCE_EXTENDED
#include <ncursesw/ncurses.h>

#include "screen.h"

#include "entity.h"

namespace eggs {

Entity::Entity(unsigned int y, unsigned int x, wchar_t icon_char) : 
  y_{y}, x_{x} {
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

