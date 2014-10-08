#include <ncurses.h>

#include "screen.h"

namespace eggs{

Screen::Screen(){
  initscr(); // start up ncurses display
  cbreak();  // disable input buffering and control character processing
  noecho();  // do not display typed characters to the screen
  keypad(stdscr, true); // handle special keys like regular ones (ie FN, arrows)
}


Screen::~Screen(){
  endwin(); 
}

void Screen::update(){
  printw("Hello World!");
  refresh();
  getch();
}

}
