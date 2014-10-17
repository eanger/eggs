#include <iostream>

#include "screen.h"
#include "input.h"
#include "world.h"

#include "engine.h"

using namespace std;

namespace {
const unsigned int kScreenWidth = 640;
const unsigned int kScreenHeight = 480;
}

namespace eggs {

void start_engine() {
  Screen screen{kScreenWidth, kScreenHeight};
  World world;
  bool gameOver = false;
  while(!gameOver){
    // key == -1 means no key pressed
    auto key = get_input_action(screen);
    gameOver = world.update(key);
    screen.render(world);
  }
}

}

