#include <iostream>

#include "utils/easylogging++.h"
#include "screen.h"
#include "input.h"
#include "world.h"

#include "engine.h"

using namespace std;

namespace eggs {

void start_engine() {
  Input input;
  World world;
  Screen screen;
  while(!world.is_game_over_){
    input.update();
    world.update(input);
    screen.update(input, world);
  }
}

}

