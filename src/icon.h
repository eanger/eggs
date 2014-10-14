#pragma once

#ifndef _XOPEN_SOURCE_EXTENDED
#define _XOPEN_SOURCE_EXTENDED
#endif
#include <ncursesw/ncurses.h>

namespace eggs{
struct Icon : public cchar_t {};
}
