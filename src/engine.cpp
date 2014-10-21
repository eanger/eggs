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
const unsigned int kDrawFrameTimePeriodMS = 500;

bool doUpdateFrameTime = true;
unsigned int frame_time_callback(unsigned int interval, void* param){
  doUpdateFrameTime = true;
  return interval;
}
}

namespace eggs {

void start_engine() {
  Screen screen{kScreenWidth, kScreenHeight};
  World world;
  bool gameOver = false;
  auto frame_time = double{0};
  auto ticks_per_sec = (double) SDL_GetPerformanceFrequency();
  auto frame_time_timer = SDL_AddTimer(kDrawFrameTimePeriodMS,
                                       frame_time_callback,
                                       nullptr);
  while(!gameOver){
    auto start_ticks = SDL_GetPerformanceCounter();
    auto key = get_input_action();
    gameOver = world.update(key);
    screen.render(world);
    // Difference in ticks over ticks per second.
    auto end_ticks = SDL_GetPerformanceCounter();
    auto elapsed_time = (end_ticks - start_ticks) / ticks_per_sec;
    if(doUpdateFrameTime){
      doUpdateFrameTime = false;
      frame_time = elapsed_time;
    }
    screen.draw_frame_time(frame_time, world);
    screen.draw();
  }
}

}

