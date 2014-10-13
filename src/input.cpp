#ifndef _XOPEN_SOURCE_EXTENDED
#define _XOPEN_SOURCE_EXTENDED
#endif
#include <ncursesw/ncurses.h>

#include "input.h"

namespace eggs {

int get_key_pressed(){
  return getch();
}

}

