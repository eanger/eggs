#pragma once

namespace eggs {
class Position {
  public:
    Position(unsigned int x, unsigned int y) : x_{x}, y_{y} {}
    Position(float x, float y) : x_{(unsigned int) x}, y_{(unsigned int) y} {}
    unsigned int x_, y_;
  private:
};
}
