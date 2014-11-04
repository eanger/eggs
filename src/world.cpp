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
      new_obj_index_{-1},
      is_game_over_{false},
      brush_{Entity::Tile::CHAIR}
  {
  random_device rd;
  default_random_engine eng(rd());
  uniform_int_distribution<int> dist(0,2);
  for(unsigned int i = 0; i < kWorldWidth; ++i){
    for(unsigned int j = 0; j < kWorldHeight; ++j){
      if(i == 0 || i == kWorldHeight - 1 ||
         j == 0 || j == kWorldWidth - 1){
        auto ent = new Entity{Entity::Tile::WALL, glm::vec2{i, j}};
        entities_.emplace_back(ent);
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
        if(new_obj_index_ != -1){
          entities_[new_obj_index_]->position_ = glm::floor(mouse_pos);
        }
        break;
      case Input::Action::MOUSE_BUTTON_DOWN:
        {
        new_obj_index_ = entities_.size();
        auto ent_pos = camera_to_world(input.mouse_loc, camera_);
        auto ent = new Entity{brush_, glm::floor(ent_pos)};
        entities_.emplace_back(ent);
        break;
        }
      case Input::Action::MOUSE_BUTTON_UP:
        new_obj_index_ = -1; /* sentinel for no entity */
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
        brush_ = Entity::Tile::CHAIR;
        break;
      case Input::Action::DESK:
        brush_ = Entity::Tile::DESK;
        break;
      case Input::Action::DOOR:
        brush_ = Entity::Tile::DOOR;
        break;
      case Input::Action::WORKER:
        brush_ = Entity::Tile::WORKER;
        break;
      case Input::Action::WALL:
        brush_ = Entity::Tile::WALL;
        break;
      default:
        break;
    }
  }
  for(auto& entity : entities_){
    entity->update(*this);
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

