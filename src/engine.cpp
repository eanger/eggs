#include <iostream>

#include "screen.h"
#include "input.h"
#include "world.h"

#include "engine.h"

using namespace std;

namespace eggs {

void start_engine() {
  Screen screen;
  World world;
  unsigned int xloc = 0;
  unsigned int yloc = 0;
  for(;;){
    auto key = get_key_pressed();
    if(key == 'q'){ return; }
    world.update(key);
    world.draw(&screen);
    screen.update();
  }
}

}

