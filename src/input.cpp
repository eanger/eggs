#include "SDL.h"

#include "screen.h"

#include "input.h"

namespace eggs {

InputAction get_input_action(){
  SDL_Event event;
  while(SDL_PollEvent(&event)){
    switch(event.type){
    case SDL_QUIT:
      return InputAction::QUIT;
    case SDL_KEYDOWN:
      switch(event.key.keysym.sym){
        case SDLK_q:
          return InputAction::QUIT;
        case SDLK_w:
          return InputAction::UP;
        case SDLK_s:
          return InputAction::DOWN;
        case SDLK_a:
          return InputAction::LEFT;
        case SDLK_d:
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

