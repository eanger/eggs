#pragma once

#include "icon.h"

namespace eggs {
struct Screen;
struct Entity {
  Icon icon_;
  Entity(wchar_t icon_char);
};
}
