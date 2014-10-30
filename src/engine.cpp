#include <iostream>

#include "utils/easylogging++.h"
#include "screen.h"
#include "input.h"
#include "world.h"

#include "engine.h"

using namespace std;

namespace {
const unsigned int kDrawFrameTimePeriodMS = 500;

bool doUpdateFrameTime = true;
unsigned int frame_time_callback(unsigned int interval, void* param){
  (void) param; //param is unused
  doUpdateFrameTime = true;
  return interval;
}
}

namespace eggs {

void start_engine() {
  Input input;
  World world;
  Screen screen;
  auto frame_time = double{0};
  auto ticks_per_sec = (double) SDL_GetPerformanceFrequency();
  SDL_AddTimer(kDrawFrameTimePeriodMS, frame_time_callback, nullptr);
  while(world.state_ != World::State::GAME_OVER){
    auto start_ticks = SDL_GetPerformanceCounter();
    input.update();
    world.update(input);
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

