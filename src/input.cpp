#include "SDL.h"

#include "utils/easylogging++.h"
#include "state.h"
#include "position.h"

#include "input.h"

namespace eggs {

void read_input(State& state){
  SDL_Event event;
  while(SDL_PollEvent(&event)){
    switch(event.type){
    case SDL_QUIT:
      state.input_actions.push(Action::QUIT);
      break;
    case SDL_KEYDOWN:
      switch(event.key.keysym.sym){
        case SDLK_q:
          state.input_actions.push(Action::QUIT);
          break;
        case SDLK_w:
          state.input_actions.push(Action::UP);
          break;
        case SDLK_s:
          state.input_actions.push(Action::DOWN);
          break;
        case SDLK_a:
          state.input_actions.push(Action::LEFT);
          break;
        case SDLK_d:
          state.input_actions.push(Action::RIGHT);
          break;
        case SDLK_z:
          state.input_actions.push(Action::DESK);
          break;
        case SDLK_x:
          state.input_actions.push(Action::CHAIR);
          break;
        case SDLK_c:
          state.input_actions.push(Action::DOOR);
          break;
        case SDLK_v:
          state.input_actions.push(Action::WORKER);
          break;
        case SDLK_b:
          state.input_actions.push(Action::WALL);
          break;
        case SDLK_BACKQUOTE:
          state.input_actions.push(Action::DEBUG);
          break;
        default:
          break;
      }
      break;
    case SDL_MOUSEMOTION:
      state.input_actions.push(Action::MOUSE_MOVE);
      state.mouse_loc = Position{static_cast<unsigned int>(event.motion.x),
                                 static_cast<unsigned int>(event.motion.y)};
      break;
    case SDL_MOUSEBUTTONDOWN:
      state.input_actions.push(Action::MOUSE_BUTTON_DOWN);
      break;
    case SDL_MOUSEBUTTONUP:
      state.input_actions.push(Action::MOUSE_BUTTON_UP);
      break;
    default:
      break;
    }
  }
}

}

