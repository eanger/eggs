#include <iostream>
#include <memory>
#include <random>
#include <sstream>
#include <string>

#include "utils/easylogging++.h"
#include "utils/glm/glm.hpp"

#include "input.h"
#include "timer.h"
#include "entity.h"

#include "world.h"

using namespace std;

namespace eggs {

World::World()
    : is_debug_{true},
      is_game_over_{false}
  {
  random_device rd;
  default_random_engine eng(rd());
  uniform_int_distribution<int> dist(0,2);
  for(unsigned int i = 0; i < kWorldWidth; ++i){
    for(unsigned int j = 0; j < kWorldHeight; ++j){
      if(i == 0 || i == kWorldHeight - 1 ||
         j == 0 || j == kWorldWidth - 1){
        Position pos{j, i};
        auto ent = new Entity{Tile::WALL, pos};
        map_[pos].reset(ent);
      }
    }
  }
}

void World::update(Input& input) {
  timer_.reset();
  timer_.start();
  while(!input.actions_.empty()){
    const auto action = input.actions_.front();
    input.actions_.pop();
    switch(action){
      case Input::Action::QUIT:
        is_game_over_ = true;
        break;
      case Input::Action::MOUSE_MOVE:
        mouse_pos = camera_to_world(input.mouse_loc, camera_);
        if(new_obj_){
          auto floored = glm::floor(mouse_pos);
          map_[*new_obj_].swap(map_[Position{floored.x, floored.y}]);
        }
        break;
      case Input::Action::MOUSE_BUTTON_DOWN:
        {
        auto floored_pos = glm::floor(camera_to_world(input.mouse_loc, camera_));
        Position pos{floored_pos.x, floored_pos.y};
        auto ent = new Entity{brush_, pos};
        map_[pos].reset(ent);
        break;
        }
      case Input::Action::MOUSE_BUTTON_UP:
        new_obj_.reset(nullptr);
        break;
      case Input::Action::DEBUG:
        is_debug_ = !is_debug_; // toggle debug state
        break;
      case Input::Action::UP:
        camera_.move_up();
        mouse_pos = camera_to_world(input.mouse_loc, camera_);
        break;
      case Input::Action::DOWN:
        camera_.move_down();
        mouse_pos = camera_to_world(input.mouse_loc, camera_);
        break;
      case Input::Action::LEFT:
        camera_.move_left();
        mouse_pos = camera_to_world(input.mouse_loc, camera_);
        break;
      case Input::Action::RIGHT:
        camera_.move_right();
        mouse_pos = camera_to_world(input.mouse_loc, camera_);
        break;
      case Input::Action::CHAIR:
        brush_ = Tile::CHAIR;
        break;
      case Input::Action::DESK:
        brush_ = Tile::DESK;
        break;
      case Input::Action::DOOR:
        brush_ = Tile::DOOR;
        break;
      case Input::Action::WORKER:
        brush_ = Tile::WORKER;
        break;
      case Input::Action::WALL:
        brush_ = Tile::WALL;
        break;
      default:
        break;
    }
  }
  timer_.stop();
}

void Camera::move_left() {
  position_.x -= 1.0;
}

void Camera::move_right() {
  position_.x += 1.0;
}

void Camera::move_up() {
  position_.y -= 1.0;
}

void Camera::move_down() {
  position_.y += 1.0;
}

glm::vec2 world_to_camera(glm::vec2 world_pos, const Camera& camera){
  return (world_pos - camera.get_position()) * camera.get_zoom();
}

glm::vec2 camera_to_world(glm::vec2 camera_pos, const Camera& camera){
  return (camera_pos / camera.get_zoom()) + camera.get_position();
}

}

