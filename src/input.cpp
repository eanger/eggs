#define _XOPEN_SOURCE_EXTENDED
#include <ncursesw/ncurses.h>

#include "input.h"

namespace eggs {

int get_key_pressed(){
  return getch();
}

}

