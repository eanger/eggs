#pragma once

namespace eggs {

class Input {
  public:
    Input() : action{Action::NONE} {}
    void update();

    unsigned int mouse_x, mouse_y;
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
