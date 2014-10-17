#include <SFML/Window.hpp>

#include "screen.h"

#include "input.h"

namespace eggs {

InputAction get_input_action(Screen& screen){
  sf::Event event;
  auto& win = screen.get_window();
  while(win.pollEvent(event)){
    switch(event.type){
    case sf::Event::Closed:
      return InputAction::QUIT;
    case sf::Event::KeyPressed:
      switch(event.key.code){
        case sf::Keyboard::Key::Q:
          return InputAction::QUIT;
        case sf::Keyboard::Key::W:
          return InputAction::UP;
        case sf::Keyboard::Key::S:
          return InputAction::DOWN;
        case sf::Keyboard::Key::A:
          return InputAction::LEFT;
        case sf::Keyboard::Key::D:
          return InputAction::RIGHT;
        default:
          break;
      }
    default:
      break;
    }
  }
  return InputAction::NONE;
}

}

