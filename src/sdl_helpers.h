#pragma once

#include <memory>
#include <utility>
#include <type_traits>
#include <stdexcept>

#include "SDL.h"

#include "../utils/easylogging++.h"

namespace eggs {

template<typename Resource>
using ResourceHandle = std::unique_ptr<Resource, void(*)(Resource*)>;

template<typename Creator, typename Destructor, typename... Arguments>
auto make_resource(
    Creator creator, Destructor destructor, Arguments&&... args)
  -> ResourceHandle<typename std::decay<decltype(*creator(std::forward<Arguments>(args)...))>::type>
{
  auto resource = creator(std::forward<Arguments>(args)...);
  if(!resource) {
    LOG(ERROR) << "Unable to create resource: " << SDL_GetError();
  }
  return {resource, destructor};
}

using ScopedCallHandle = std::unique_ptr<void*, std::function<void(void*)> >;
template<typename Creator, typename Destructor, typename... Arguments>
ScopedCallHandle make_scoped_call(Creator creator,
                      Destructor destructor,
                      Arguments&&... args) {
  auto res = creator(std::forward<Arguments>(args)...);
  if(res){
    LOG(ERROR) << "Failed initial scope call: " << SDL_GetError();
  }
  auto deleter = [=](void*){ destructor(); };
  return std::unique_ptr<void*,decltype(deleter)>(nullptr, deleter);
}

}
