#pragma once

namespace eggs {
class Position {
  public:
    Position() : x_{0}, y_{0} {}
    Position(unsigned int x, unsigned int y) : x_{x}, y_{y} {}
    unsigned int x_, y_;
  private:
};
}
