#include <iostream>
#include <SDL2/SDL.h>

#include "sdl_helpers.h"
#include "engine.h"

using namespace std;

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

  auto surface = sdl2::make_resource(SDL_CreateRGBSurface,
                                     SDL_FreeSurface,
                                     0 /* unused param */,
                                     640,
                                     480,
                                     32,
                                     0,
                                     0,
                                     0,
                                     0);

  auto texture = sdl2::make_resource(SDL_CreateTextureFromSurface,
                                     SDL_DestroyTexture,
                                     renderer.get(),
                                     surface.get());
  while(true) {
    SDL_RenderClear(renderer.get());
    SDL_RenderCopy(renderer.get(), texture.get(), NULL, NULL);
    SDL_RenderPresent(renderer.get());
    SDL_Delay(2000);
  }

  return 0;
}



