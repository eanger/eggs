#include <iostream>

#include <SFML/System/Clock.hpp>

#include "../utils/easylogging++.h"
#include "screen.h"
#include "input.h"
#include "world.h"

#include "engine.h"

using namespace std;

namespace {
const unsigned int kScreenWidth = 640;
const unsigned int kScreenHeight = 480;
const float kDrawFrameTimePeriod = 0.01f;
}

namespace eggs {

void start_engine() {
  Screen screen{kScreenWidth, kScreenHeight};
  World world;
  bool gameOver = false;
  auto last_frame_time_draw = 0.0f;
  auto frame_time = kDrawFrameTimePeriod;
  while(!gameOver){
    auto start_ticks = SDL_GetPerformanceCounter();
    auto key = get_input_action(screen);
    gameOver = world.update(key);
    screen.render(world);
    // Difference in ticks over ticks per second.
    auto elapsed_time = (SDL_GetPerformanceCounter() - start_ticks) / 
      SDL_GetPerformanceFrequency();
    last_frame_time_draw += elapsed_time;
    if(last_frame_time_draw >= kDrawFrameTimePeriod){
      last_frame_time_draw = 0.0f;
      frame_time = elapsed_time;
    }
    screen.draw_frame_time(1000 /* ms per sec */ * frame_time, world);
    screen.draw();
  }
}

}

