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
  sf::Clock clock;
  auto last_frame_time_draw = 0.0f;
  auto frame_time = kDrawFrameTimePeriod;
  while(!gameOver){
    clock.restart();
    // key == -1 means no key pressed
    auto key = get_input_action(screen);
    gameOver = world.update(key);
    screen.render(world);
    auto elapsed_time = clock.getElapsedTime();
    last_frame_time_draw += elapsed_time.asSeconds();
    if(last_frame_time_draw >= kDrawFrameTimePeriod){
      last_frame_time_draw = 0.0f;
      frame_time = elapsed_time.asSeconds();
    }
    screen.draw_frame_time(1000 /* ms per sec */ * frame_time, world);
    screen.draw();
  }
}

}

