#pragma once

#include <memory>
#include <utility>
#include <type_traits>
#include <stdexcept>

namespace eggs {

template<typename Creator, typename Destructor, typename... Arguments>
auto make_resource(Creator creator,
                   Destructor destructor,
                   Arguments&&... args) {
  auto resource = creator(std::forward<Arguments>(args)...);
  if(!resource) {
    throw std::runtime_error{"Unable to create resource"};
  }
  typedef typename std::decay<decltype(*resource)>::type ResourceType;
  return std::unique_ptr<ResourceType, void(*)(ResourceType*)>(resource,
                                                               destructor);
}

template<typename Creator, typename Destructor, typename... Arguments>
auto make_scoped_call(Creator creator,
                      Destructor destructor,
                      Arguments&&... args){
  auto res = creator(std::forward<Arguments>(args)...);
  if(res){
    throw std::runtime_error{SDL_GetError()};
  }
  auto deleter = [=](void*){ destructor(); };
  return std::unique_ptr<void*,decltype(deleter)>(nullptr, deleter);
}

}
