#pragma once

namespace eggs {
class Screen;

class Input {
  public:
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
      MOUSE_BUTTON_DOWN
    } action;
  private:
    Input() : action{Action::NONE} {}
    friend Input get_input();
};

Input get_input();
}
