#pragma once

#include "utils/glm/glm.hpp"

namespace eggs {

class Input {
  public:
    Input() : action{Action::NONE} {}
    void update();

    glm::vec2 mouse_loc;
    enum class Action{
      NONE,
      QUIT,
      LEFT,
      RIGHT,
      UP,
      DOWN,
      MOUSE_MOVE,
      MOUSE_BUTTON_UP,
      MOUSE_BUTTON_DOWN,
      DEBUG
    } action;
};

}
