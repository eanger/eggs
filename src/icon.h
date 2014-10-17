#pragma once

#include <memory>

namespace sf{
class Shape;
}

namespace eggs{
class Icon {
  std::unique_ptr<sf::Shape> shape_;
  public:
    Icon();
};
}
