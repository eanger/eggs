#include "position.h"
#include "state.h"

#include "camera.h"

namespace eggs {

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

