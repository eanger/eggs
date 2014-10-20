add_executable(eggs
engine.cpp
input.cpp
main.cpp
screen.cpp
state.cpp
world.cpp)

#set(CMAKE_PREFIX_PATH "C:/Users/Eric/Downloads/SFML-2.1-windows-gcc-4.7-mingw-32bits/SFML-2.1")
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})
find_package(SFML 2.1 REQUIRED system window graphics)
include_directories(${SFML_INCLUDE_DIR})
target_link_libraries(eggs ${SFML_LIBRARIES})

#set(ASSETSDIR "${CMAKE_BINARY_DIR}/assets")
#configure_file(config/assets.h.in config/assets.h)
#include_directories(config)
add_definitions(-DBINDIR="${CMAKE_CURRENT_BINARY_DIR}")
