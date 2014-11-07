#pragma once

#include "SDL.h"

#include "sdl_helpers.h"

namespace eggs {

struct EntityType {
  ResourceHandle<SDL_Texture> texture_;
};

}
