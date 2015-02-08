#pragma once

#include <queue>

#include "SDL.h"

#include "position.h"
#include "camera.h"
#include "assets.h"
#include "entity.h"
#include "entity_type.h"
#include "timer.h"
#include "event_queue.h"

namespace eggs{

const unsigned int kWorldWidth = 50;
const unsigned int kWorldHeight = 50;
const int kTileSize = 20;
const unsigned int kExtraScreenWidth = 0;
const unsigned int kExtraScreenHeight = 0;
const unsigned int kStartWidth = 640;
const unsigned int kStartHeight = 480;

enum class Action{
  NONE,
  QUIT,
  LEFT,
  RIGHT,
  UP,
  DOWN,
  MOUSE_MOVE,
  MOUSE_BUTTON_UP,
  MOUSE_BUTTON_DOWN,
  DEBUG,
  DESK,
  CHAIR,
  DOOR,
  WORKER,
  WALL
};

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

struct State {
  bool done;
  Position mouse_loc;
  std::queue<Action> input_actions;
  Camera camera;
  Map<std::unique_ptr<Entity>, kWorldHeight, kWorldWidth> map;
  Timer timer;
  bool is_debug;
  Entity* new_obj;
  EntityType* brush;
  EventQueue event_queue;
  EntityType chair_entity;
  EntityType desk_entity;
  EntityType door_entity;
  EntityType worker_entity;
  EntityType wall_entity;

  State(SDL_Renderer* renderer)
      : done{false}, camera{kTileSize}, is_debug{true}, new_obj{nullptr},
        chair_entity{make_resource(make_texture_resource, SDL_DestroyTexture,
                                   renderer,
                                   get_asset_path("chair.bmp").c_str())},
        desk_entity{make_resource(make_texture_resource, SDL_DestroyTexture,
                                  renderer,
                                  get_asset_path("desk.bmp").c_str())},
        door_entity{make_resource(make_texture_resource, SDL_DestroyTexture,
                                  renderer,
                                  get_asset_path("door.bmp").c_str())},
        worker_entity{make_resource(make_texture_resource, SDL_DestroyTexture,
                                    renderer,
                                    get_asset_path("guy.bmp").c_str())},
        wall_entity{make_resource(make_texture_resource, SDL_DestroyTexture,
                                  renderer,
                                  get_asset_path("walls.bmp").c_str())} {
    for (unsigned int i = 0; i < kWorldWidth; ++i) {
      for (unsigned int j = 0; j < kWorldHeight; ++j) {
        if (i == 0 || i == kWorldHeight - 1 || j == 0 || j == kWorldWidth - 1) {
          Position pos{j, i};
          auto ent = new Entity{wall_entity, pos};
          map[pos].reset(ent);
        }
      }
    }
  }
};

}
