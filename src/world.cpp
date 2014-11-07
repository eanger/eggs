#include <iostream>
#include <memory>
#include <random>
#include <sstream>
#include <string>

#include "SDL.h"

#include "utils/easylogging++.h"

#include "input.h"
#include "timer.h"
#include "entity.h"
#include "sdl_helpers.h"
#include "assets.h"

#include "world.h"

using namespace std;

namespace eggs {

World::World(SDL_Renderer* renderer)
    : is_debug_{true},
      mouse_pos{0,0},
      new_obj_{nullptr},
      is_game_over_{false},
      chair_entity_{make_resource(make_texture_resource,
                                  SDL_DestroyTexture,
                                  renderer,
                                  get_asset_path("chair.bmp").c_str())},
      desk_entity_{make_resource(make_texture_resource,
                                  SDL_DestroyTexture,
                                  renderer,
                                  get_asset_path("desk.bmp").c_str())},
      door_entity_{make_resource(make_texture_resource,
                                  SDL_DestroyTexture,
                                  renderer,
                                  get_asset_path("door.bmp").c_str())},
      worker_entity_{make_resource(make_texture_resource,
                                  SDL_DestroyTexture,
                                  renderer,
                                  get_asset_path("guy.bmp").c_str())},
      wall_entity_{make_resource(make_texture_resource,
                                  SDL_DestroyTexture,
                                  renderer,
                                  get_asset_path("walls.bmp").c_str())}
  {
  random_device rd;
  default_random_engine eng(rd());
  uniform_int_distribution<int> dist(0,2);
  for(unsigned int i = 0; i < kWorldWidth; ++i){
    for(unsigned int j = 0; j < kWorldHeight; ++j){
      if(i == 0 || i == kWorldHeight - 1 ||
         j == 0 || j == kWorldWidth - 1){
        Position pos{j, i};
        auto ent = new Entity{wall_entity_, pos};
        map_[pos].reset(ent);
      }
    }
  }
}

void World::update(Input& input) {
  timer_.reset();
  timer_.start();
  event_queue_.update();
  while(!input.actions_.empty()){
    const auto action = input.actions_.front();
    input.actions_.pop();
    switch(action){
      case Input::Action::QUIT:
        is_game_over_ = true;
        break;
      case Input::Action::MOUSE_MOVE:
        mouse_pos = camera_to_world(input.mouse_loc, camera_);
        /* move a dragged object only if the slot is vacant */
        if(new_obj_ && !map_[mouse_pos]){
          map_[new_obj_->position_].swap(map_[mouse_pos]);
          new_obj_->position_ = mouse_pos;
        }
        break;
      case Input::Action::MOUSE_BUTTON_DOWN:
        {
        if(!brush_){ 
          break;
        }
        auto pos = camera_to_world(input.mouse_loc, camera_);
        if(!map_[pos]){
          new_obj_ = new Entity{*brush_, pos};
          map_[pos].reset(new_obj_);
        }
        break;
        }
      case Input::Action::MOUSE_BUTTON_UP:
        new_obj_ = nullptr;
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
        brush_ = &chair_entity_;
        break;
      case Input::Action::DESK:
        brush_ = &desk_entity_;
        break;
      case Input::Action::DOOR:
        brush_ = &door_entity_;
        break;
      case Input::Action::WORKER:
        brush_ = &worker_entity_;
        break;
      case Input::Action::WALL:
        brush_ = &wall_entity_;
        break;
      default:
        break;
    }
  }
  timer_.stop();
}

void Camera::move_left() {
  position_.x_ = position_.x_ > 0 ? position_.x_ - 1.0 : position_.x_;
}

void Camera::move_right() {
  auto right_wall = camera_to_world(Position{kStartWidth, kStartHeight}, *this);
  position_.x_ = right_wall.x_ < kWorldWidth ? position_.x_ + 1.0 : position_.x_;
}

void Camera::move_up() {
  position_.y_ = position_.y_ > 0 ? position_.y_ - 1.0 : position_.y_;
}

void Camera::move_down() {
  auto right_wall = camera_to_world(Position{kStartWidth, kStartHeight}, *this);
  position_.y_ = right_wall.y_ < kWorldWidth ? position_.y_ + 1.0 : position_.y_;
}

Position world_to_camera(Position world_pos, const Camera& camera){
  const auto& cam = camera.get_position();
  return {(unsigned int) ((world_pos.x_ - cam.x_) * camera.get_zoom()),
          (unsigned int) ((world_pos.y_ - cam.y_) * camera.get_zoom())};
}

Position camera_to_world(Position camera_pos, const Camera& camera){
  const auto& cam = camera.get_position();
  return {(unsigned int) (camera_pos.x_ / camera.get_zoom() + cam.x_),
          (unsigned int) (camera_pos.y_ / camera.get_zoom() + cam.y_)};
}

}

