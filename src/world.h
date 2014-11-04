#pragma once

#include <vector>
#include <memory>

#include "utils/glm/glm.hpp"
#include "timer.h"
#include "entity.h"

namespace eggs {

const unsigned int kWorldWidth = 50;
const unsigned int kWorldHeight = 50;
const int kTileSize = 20;
const unsigned int kExtraScreenWidth = 0;
const unsigned int kExtraScreenHeight = 0;
const unsigned int kStartWidth = 640;
const unsigned int kStartHeight = 480;

class Input;

class Camera {
  public:
    Camera() : zoom_{kTileSize}, position_{0, 0} {}
    void move_left();
    void move_right();
    void move_up();
    void move_down();
    glm::vec2 get_position() const { return position_; }
    float get_zoom() const { return zoom_; }
  private:
    float zoom_;
    glm::vec2 position_;
};

glm::vec2 world_to_camera(glm::vec2 world_pos, const Camera& camera);
glm::vec2 camera_to_world(glm::vec2 camera_pos, const Camera& camera);

class World {
  public:
  std::vector<std::unique_ptr<Entity>> entities_;
  bool is_debug_;
  Timer timer_;
  Camera camera_;
  glm::vec2 mouse_pos;
  int new_obj_index_;
  bool is_game_over_;
  Entity::Tile brush_;

  World();
  void update(Input& input);
};
}
