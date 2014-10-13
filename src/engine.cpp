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
  bool gameOver = false;
  while(!gameOver){
    auto key = get_key_pressed();
    gameOver = world.update(key);
    screen.clear();
    world.draw(&screen);
    screen.update();
  }
}

}

