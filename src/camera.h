#pragma once

#include "position.h"

namespace eggs {

class Camera {
  public:
    Camera(float zoom) : zoom_{zoom}, position_{0u, 0u} {}
    void move_left();
    void move_right();
    void move_up();
    void move_down();
    Position get_position() const { return position_; }
    float get_zoom() const { return zoom_; }
  private:
    float zoom_;
    Position position_; /* Position of the camera in world coordinates */
};

Position world_to_camera(Position world_pos, const Camera& camera);
Position camera_to_world(Position camera_pos, const Camera& camera);

}
