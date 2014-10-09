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
  uint xloc = 0;
  uint yloc = 0;
  for(;;){
    auto key = get_key_pressed();
    if(key == 'q'){ return; }
    else {
      world.add_entity(++yloc,++xloc,L'9');
    }
    world.update();
    world.draw(&screen);
    screen.update();
  }
}

}

