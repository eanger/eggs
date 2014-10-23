#include "SDL.h"

#include "screen.h"

#include "input.h"

namespace eggs {

Input get_input(){
  Input input;
  SDL_Event event;
  while(SDL_PollEvent(&event)){
    switch(event.type){
    case SDL_QUIT:
      input.action = Input::Action::QUIT;
      break;
    case SDL_KEYDOWN:
      switch(event.key.keysym.sym){
        case SDLK_q:
          input.action = Input::Action::QUIT;
          break;
        case SDLK_w:
          input.action = Input::Action::UP;
          break;
        case SDLK_s:
          input.action = Input::Action::DOWN;
          break;
        case SDLK_a:
          input.action = Input::Action::LEFT;
          break;
        case SDLK_d:
          input.action = Input::Action::RIGHT;
          break;
        default:
          break;
      }
      break;
    case SDL_MOUSEMOTION:
      input.action = Input::Action::MOUSE_MOVE;
      input.mouse_x = event.motion.x;
      input.mouse_y = event.motion.y;
      break;
    case SDL_MOUSEBUTTONDOWN:
      input.action = Input::Action::MOUSE_BUTTON_DOWN;
      break;
    case SDL_MOUSEBUTTONUP:
      input.action = Input::Action::MOUSE_BUTTON_UP;
      break;
    default:
      break;
    }
  }
  return input;
}

}

