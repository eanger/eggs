#include <iostream>
#include <SDL2/SDL.h>
//#include <SDL2/SDL_ttf.h>

#include "sdl_helpers.h"
#include "engine.h"
#include "state.h"

using namespace std;

namespace {
const double kMSPerUpdate = 10;
}

namespace eggs {

int start_engine() {
  auto sdl_systems_init = sdl2::make_scoped_call(SDL_Init,
                                                 SDL_Quit,
                                                 SDL_INIT_VIDEO);

  auto window = sdl2::make_resource(SDL_CreateWindow,
                                    SDL_DestroyWindow, 
                                    "Main Window",
                                    SDL_WINDOWPOS_CENTERED,
                                    SDL_WINDOWPOS_CENTERED,
                                    640,
                                    480,
                                    SDL_WINDOW_OPENGL);

  auto renderer = sdl2::make_resource(SDL_CreateRenderer,
                                      SDL_DestroyRenderer,
                                      window.get(),
                                      -1 /* first available renderer */,
                                      SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

  auto last_tick_count = SDL_GetTicks();
  auto lag = uint32_t{0};
  while(true) {
    State state{State::CONTINUE};
    auto cur_tick_count = SDL_GetTicks();
    auto elapsed_ticks = cur_tick_count - last_tick_count;
    last_tick_count = cur_tick_count;
    auto num_updates = uint32_t{0};
    for(lag += elapsed_ticks; lag >= kMSPerUpdate; lag -= kMSPerUpdate){
      // update
      update(state, kMSPerUpdate);
      if(state == State::QUIT){
        return 0;
      }
    }

    auto fps = 1 /* frame */ / (elapsed_ticks / 1000.0 /* ms per sec */ );
    cout << fps << " fps" << endl;
    // render
    SDL_RenderClear(renderer.get());
    SDL_RenderPresent(renderer.get());
  }

  return 0;
}

void update(State& state, uint32_t elapsed_ms){
  state = State::CONTINUE;
  SDL_Event event;
  while(SDL_PollEvent(&event)){
    if(event.type == SDL_KEYDOWN ||
       event.type == SDL_QUIT){
      state = State::QUIT;
    }
  }
}

}

