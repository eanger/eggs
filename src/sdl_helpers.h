#ifndef SDL_HELPERS_H
#define SDL_HELPERS_H

#include <memory>
#include <utility>
#include <type_traits>
#include <stdexcept>

namespace eggs { namespace sdl2 {
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
} }

#endif // SDL_HELPERS_H
