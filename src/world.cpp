#include <iostream>
#include <memory>
#include <random>
#include <sstream>
#include <string>

#include "utils/easylogging++.h"

#include "input.h"
#include "timer.h"
#include "entity.h"
#include "state.h"

#include "world.h"

using namespace std;

namespace {

void process_input(State* state) {
  while(!state->input_actions.empty()){
    const auto action = state->input_actions.front();
    state->input_actions.pop();
    switch(action){
      case Action::QUIT: {
        state->done = true;
        return;
      } break;
      case Action::MOUSE_MOVE: {
        auto mouse_pos = camera_to_world(state->mouse_loc, state->camera);
        /* move a dragged object only if the slot is vacant */
        if(state->new_obj && !state->map[mouse_pos]){
          state->map[state->new_obj->position_].swap(state->map[mouse_pos]);
          state->new_obj->position_ = mouse_pos;
        }
      } break;
      case Action::MOUSE_BUTTON_DOWN: {
        if(!state->brush){ 
          break;
        }
        auto pos = camera_to_world(state->mouse_loc, state->camera);
        if(!state->map[pos]){
          state->new_obj = new Entity{*state->brush, pos};
          state->map[pos].reset(state->new_obj);
        }
      } break;
      case Action::MOUSE_BUTTON_UP: {
        state->new_obj = nullptr;
      } break;
      case Action::DEBUG: {
        state->is_debug = !state->is_debug; // toggle debug state
      } break;
      case Action::UP: {
        state->camera.move_up();
      } break;
      case Action::DOWN: {
        state->camera.move_down();
      } break;
      case Action::LEFT: {
        state->camera.move_left();
      } break;
      case Action::RIGHT: {
        state->camera.move_right();
      } break;
      case Action::CHAIR: {
        state->brush = &state->chair_entity;
      } break;
      case Action::DESK: {
        state->brush = &state->desk_entity;
      } break;
      case Action::DOOR: {
        state->brush = &state->door_entity;
      } break;
      case Action::WORKER: {
        state->brush = &state->worker_entity;
      } break;
      case Action::WALL: {
        state->brush = &state->wall_entity;
      } break;
      default: {
      } break;
    }
  }
}

} // end unnamed namespace

namespace eggs {

extern "C" void update(State* state) {
  state->timer.reset();
  state->timer.start();

  process_input(state);
  state->event_queue.update();

  state->timer.stop();
}

} // end namespace eggs

