#pragma once

#include <queue>

#include "position.h"

namespace eggs {

class Input {
  public:
    void update();

    Position mouse_loc;
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
      DEBUG,
      DESK,
      CHAIR,
      DOOR,
      WORKER,
      WALL
    };
    std::queue<Action> actions_;
};

}
