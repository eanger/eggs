#pragma once

#include <vector>
#include <memory>

#include "timer.h"
#include "position.h"
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
class Entity;
enum class Tile;

template <typename T, int Rows, int Cols>
class Map {
  public:
    T& operator[](const Position& pos) {
      return map_[pos.y_][pos.x_];
    }
    const T& operator[](const Position& pos) const {
      return map_[pos.y_][pos.x_];
    }
  private:
    T map_[Rows][Cols];
};

class Camera {
  public:
    Camera() : zoom_{kTileSize}, position_{0u, 0u} {}
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

class World {
  public:
  Map<std::unique_ptr<Entity>, kWorldHeight, kWorldWidth> map_;
  bool is_debug_;
  Timer timer_;
  Camera camera_;
  Position mouse_pos;
  Entity* new_obj_;
  bool is_game_over_;
  Tile brush_;

  World();
  void update(Input& input);
};
}
