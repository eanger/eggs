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
  while(world.state_ != World::State::GAME_OVER){
    input.update();
    world.update(input);
    screen.update(world);
  }
}

}

