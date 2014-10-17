#pragma once

namespace eggs {
class Screen;

enum class InputAction{
  NONE,
  QUIT,
  LEFT,
  RIGHT,
  UP,
  DOWN
};

InputAction get_input_action(Screen& screen);
}
