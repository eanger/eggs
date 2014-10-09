#include <clocale>
#include <stdexcept>

#define _XOPEN_SOURCE_EXTENDED
#include <ncursesw/ncurses.h>

#include "screen.h"

namespace eggs{

Screen::Screen(){
  if(setlocale(LC_ALL, "") == nullptr){ // set unicode locale
    throw std::runtime_error("Cannot set locale.");
  }
  if(initscr() == nullptr){ // start up ncurses display
    throw std::runtime_error("Cannot initialize ncurses.");
  }
  if(cbreak() == ERR){  // disable input buffering and control character processing
    throw std::runtime_error("Cannot disable input buffering");
  }
  if(noecho() == ERR){ // do not display typed characters to the screen
    throw std::runtime_error("Cannot turn off echo");
  }
  if(keypad(stdscr, true) == ERR){ // handle FN/arrows like regular keys 
    throw std::runtime_error("Cannot turn on keypad handling");
  }
}


Screen::~Screen(){
  endwin(); 
}

void Screen::update(){
  refresh();
}

void Screen::draw_char_at(const cchar_t& icon, unsigned int y, unsigned int x){
  mvadd_wch(y, x, &icon);
}

}
