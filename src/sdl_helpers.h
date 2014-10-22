#pragma once

#include <memory>
#include <utility>
#include <type_traits>
#include <stdexcept>

#include "SDL.h"

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
    throw std::runtime_error{SDL_GetError()};
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
    throw std::runtime_error{SDL_GetError()};
  }
  auto deleter = [=](void*){ destructor(); };
  return std::unique_ptr<void*,decltype(deleter)>(nullptr, deleter);
}

}
