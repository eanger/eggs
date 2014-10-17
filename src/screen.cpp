#include <clocale>
#include <stdexcept>
#include <sstream>

#include <SFML/Graphics.hpp>

#include "icon.h"
#include "world.h"

#include "screen.h"

using namespace std;

namespace {
const unsigned int kTileSize = 10;
}

namespace eggs{

void Screen::print_line_at(const std::string& line,
                           unsigned int y,
                           unsigned int x) {
  sf::Text text{line, font_};
  text.setPosition(x, y);
  window_.draw(text);
}

void Screen::print_line_centered(const std::string& line, unsigned int y) {
  sf::Text text{line, font_};
  auto bounds = text.getGlobalBounds();
  auto size = window_.getSize();
  print_line_at(line, (size.x - bounds.width) / 2, y);
}

Screen::Screen(unsigned int width, unsigned int height): 
  window_{sf::VideoMode(width, height), "EGGS"},
  token_{{kTileSize,kTileSize}},
  player_{{kTileSize,kTileSize}},
  wall_{{kTileSize,kTileSize}} {

  token_.setFillColor(sf::Color::White);
  player_.setFillColor(sf::Color::Red);
  wall_.setFillColor(sf::Color::Cyan);
  if(!font_.loadFromFile(ASSETS_DIR "/Sail-Regular.otf")){
    //throw std::runtime_error("Unable to load font");
  }
}

void Screen::render(const World& world){
  window_.clear(sf::Color::Black);
  // Do the actual rendering of world contents
  unsigned int start_x = 0, start_y = 0;
  for(const auto& row : world.map_){
    for(const auto& tile : row){
      sf::Shape* shape{nullptr};
      switch(tile){
        case World::Tile::TOKEN:
          shape = &token_;
          break;
        case World::Tile::PLAYER:
          shape = &player_;
          break;
        case World::Tile::WALL:
          shape = &wall_;
          break;
        case World::Tile::EMPTY:
          break;
      }
      if(shape){
        shape->setPosition(start_x, start_y);
        window_.draw(*shape);
      }
      start_x += kTileSize;
    }
    start_y += kTileSize;
    start_x = 0;
  }
  stringstream score_str;
  score_str << "Score: " 
            << world.score_ 
            << "\nMoves Left: " 
            << world.moves_left_;
  print_line_at(score_str.str(), kTileSize * world.map_.size(), 0);

  window_.display();
}

void Screen::draw_icon_at(const Icon& icon, unsigned int y, unsigned int x){
}

sf::RenderWindow& Screen::get_window() {
  return window_;
}

}
