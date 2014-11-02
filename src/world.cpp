#include <iostream>
#include <memory>
#include <random>
#include <sstream>
#include <string>

#include "utils/easylogging++.h"

#include "input.h"
#include "timer.h"

#include "world.h"

using namespace std;

namespace eggs {

World::World()
    : state_{State::START},
      is_debug_{true},
      new_obj_index_{-1}
  {
  random_device rd;
  default_random_engine eng(rd());
  uniform_int_distribution<int> dist(0,2);
  for(unsigned int i = 0; i < kWorldWidth; ++i){
    for(unsigned int j = 0; j < kWorldHeight; ++j){
      if(i == 0 || i == kWorldHeight - 1 ||
         j == 0 || j == kWorldWidth - 1){
        entity_positions_.emplace_back(i, j);
        entity_types_.emplace_back(Tile::WALL);
      }
    }
  }
}

void World::update(const Input& input) {
  timer_.reset();
  timer_.start();
  switch(state_){
    case State::START:
      state_ = State::PLAYING;
      break;
    case State::PLAYING:
      switch(input.action){
        case Input::Action::QUIT:
          state_ = State::GAME_OVER;
          break;
        case Input::Action::MOUSE_MOVE:
          mouse_pos = camera_to_world(input.mouse_loc, camera_);
          if(new_obj_index_ != -1){
            entity_positions_[new_obj_index_] = glm::floor(mouse_pos);
          }
          break;
        case Input::Action::MOUSE_BUTTON_DOWN:
          {
          new_obj_index_ = entity_types_.size();
          entity_types_.emplace_back(Tile::TOKEN);
          auto ent_pos = camera_to_world(input.mouse_loc, camera_);
          entity_positions_.emplace_back(floor(ent_pos.x), floor(ent_pos.y));
          break;
          }
        case Input::Action::MOUSE_BUTTON_UP:
          new_obj_index_ = -1; /* sentinel for no entity */
          break;
        case Input::Action::DEBUG:
          is_debug_ = !is_debug_; // toggle debug state
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
        default:
          break;
      }
      break;
    default:
      throw runtime_error("Invalid game state");
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

