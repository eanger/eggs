#include <clocale>
#include <stdexcept>

#ifndef _XOPEN_SOURCE_EXTENDED
#define _XOPEN_SOURCE_EXTENDED
#endif
#include <ncursesw/ncurses.h>
#include <ncursesw/panel.h>

#include "icon.h"

#include "screen.h"

namespace eggs{

void Screen::clear() {
  erase();
}

void Screen::print_line_at(const std::string& line,
                           unsigned int y,
                           unsigned int x) {
  mvprintw(y, x, line.c_str());
}

void Screen::print_line_centered(const std::string& line, unsigned int y) {
  int row, col;
  getmaxyx(stdscr, row, col);
  print_line_at(line, y, (col - line.length()) / 2);
}

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
  if(curs_set(0) == ERR){ // hide cursor
    throw std::runtime_error("Cannot hide cursor");
  }
}


Screen::~Screen(){
  endwin(); 
}

void Screen::update(){
  refresh();
}

void Screen::draw_icon_at(const Icon& icon, unsigned int y, unsigned int x){
  mvadd_wch(y, x, &icon);
}

}
