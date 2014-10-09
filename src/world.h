#pragma once

#include <memory>
#include <vector>

#include "entity.h"

namespace eggs {
class World {
  std::vector<std::unique_ptr<Entity>> entities_;

  public:
  void update();
  void draw(Screen* screen);
  void add_entity(unsigned int y, unsigned int x, wchar_t icon_char);
};
}
