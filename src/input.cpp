#include "SDL.h"

#include "utils/glm/glm.hpp"
#include "utils/easylogging++.h"
#include "screen.h"

#include "input.h"

namespace eggs {

void Input::update(){
  action = Input::Action::NONE;
  SDL_Event event;
  while(SDL_PollEvent(&event)){
    switch(event.type){
    case SDL_QUIT:
      action = Input::Action::QUIT;
      break;
    case SDL_KEYDOWN:
      switch(event.key.keysym.sym){
        case SDLK_q:
          action = Input::Action::QUIT;
          break;
        case SDLK_w:
          action = Input::Action::UP;
          break;
        case SDLK_s:
          action = Input::Action::DOWN;
          break;
        case SDLK_a:
          action = Input::Action::LEFT;
          break;
        case SDLK_d:
          action = Input::Action::RIGHT;
          break;
        case SDLK_BACKQUOTE:
          action = Input::Action::DEBUG;
          break;
        default:
          break;
      }
      break;
    case SDL_MOUSEMOTION:
      action = Input::Action::MOUSE_MOVE;
      mouse_loc = glm::vec2(event.motion.x, event.motion.y);
      break;
    case SDL_MOUSEBUTTONDOWN:
      action = Input::Action::MOUSE_BUTTON_DOWN;
      break;
    case SDL_MOUSEBUTTONUP:
      action = Input::Action::MOUSE_BUTTON_UP;
      break;
    default:
      break;
    }
  }
}

}

