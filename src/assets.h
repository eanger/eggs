#pragma once

#include <string>

#include "SDL.h"

namespace eggs {

std::string get_asset_path(std::string name) {
  static std::string assets_path = SDL_GetBasePath();

  return assets_path + "/../assets/" + name;
}

}
