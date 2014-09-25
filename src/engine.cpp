#include <iostream>
#include <SDL2/SDL.h>

#include "sdl_helpers.h"
#include "engine.h"

using namespace std;

namespace {
const double kMSPerUpdate = 1;
}

namespace eggs {

int start_engine() {

  if(SDL_Init(SDL_INIT_VIDEO) != 0){
    cerr << "SDL_Init error: " << SDL_GetError() << endl;
    return 1;
  }

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
    auto cur_tick_count = SDL_GetTicks();
    for(lag += cur_tick_count - last_tick_count;
        lag >= kMSPerUpdate; lag -= kMSPerUpdate){
      // update
    }
    // render
    SDL_RenderClear(renderer.get());
    SDL_RenderPresent(renderer.get());
    SDL_Delay(2000);
  }

  SDL_Quit();
  return 0;
}

}

