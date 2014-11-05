#include "SDL.h"

#include "utils/easylogging++.h"
#include "screen.h"

#include "input.h"

namespace eggs {

void Input::update(){
  SDL_Event event;
  while(SDL_PollEvent(&event)){
    switch(event.type){
    case SDL_QUIT:
      actions_.push(Input::Action::QUIT);
      break;
    case SDL_KEYDOWN:
      switch(event.key.keysym.sym){
        case SDLK_q:
          actions_.push(Input::Action::QUIT);
          break;
        case SDLK_w:
          actions_.push(Input::Action::UP);
          break;
        case SDLK_s:
          actions_.push(Input::Action::DOWN);
          break;
        case SDLK_a:
          actions_.push(Input::Action::LEFT);
          break;
        case SDLK_d:
          actions_.push(Input::Action::RIGHT);
          break;
        case SDLK_z:
          actions_.push(Input::Action::DESK);
          break;
        case SDLK_x:
          actions_.push(Input::Action::CHAIR);
          break;
        case SDLK_c:
          actions_.push(Input::Action::DOOR);
          break;
        case SDLK_v:
          actions_.push(Input::Action::WORKER);
          break;
        case SDLK_b:
          actions_.push(Input::Action::WALL);
          break;
        case SDLK_BACKQUOTE:
          actions_.push(Input::Action::DEBUG);
          break;
        default:
          break;
      }
      break;
    case SDL_MOUSEMOTION:
      actions_.push(Input::Action::MOUSE_MOVE);
      mouse_loc = Position{static_cast<unsigned int>(event.motion.x),
                           static_cast<unsigned int>(event.motion.y)};
      break;
    case SDL_MOUSEBUTTONDOWN:
      actions_.push(Input::Action::MOUSE_BUTTON_DOWN);
      break;
    case SDL_MOUSEBUTTONUP:
      actions_.push(Input::Action::MOUSE_BUTTON_UP);
      break;
    default:
      break;
    }
  }
}

}

