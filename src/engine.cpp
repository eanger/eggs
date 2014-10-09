#include <iostream>

#include "screen.h"
#include "input.h"

#include "engine.h"

using namespace std;

namespace eggs {

void start_engine() {
  Screen screen;
  for(;;){
    auto key = get_key_pressed();
    if(key == 'q'){ return; }
    screen.update();
  }
}

}

