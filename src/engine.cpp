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
  bool gameOver = world.update(0 /* no key */);
  screen.clear();
  world.draw(&screen);
  screen.update();
  while(!gameOver){
    // key == -1 means no key pressed
    auto key = get_key_pressed();
    gameOver = world.update(key);
    screen.clear();
    world.draw(&screen);
    screen.update();
  }
}

}

