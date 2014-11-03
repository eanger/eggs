#pragma once

#include <queue>

#include "utils/glm/glm.hpp"

namespace eggs {

class Input {
  public:
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
    };
    std::queue<Action> actions_;
};

}
