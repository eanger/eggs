#include "screen.h"
#include "icon.h"

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

