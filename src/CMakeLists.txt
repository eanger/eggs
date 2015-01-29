add_library(eggs SHARED
entity.h
entity_type.h
event_queue.h
state.h
world.cpp
world.h
)

add_executable(eggs-bin
assets.h
camera.cpp
camera.h
entity.h
entity_type.h
event_queue.h
event_queue.cpp
input.cpp
input.h
main.cpp
screen.cpp
screen.h
sdl_helpers.h
state.h
timer.cpp
timer.h
)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})
find_package(SDL2 REQUIRED)
find_package(SDL2TTF REQUIRED)
find_package(SDL2IMAGE REQUIRED)
include_directories(${SDL2_INCLUDE_DIR} ${SDL2TTF_INCLUDE_DIR} ${SDL2IMAGE_INCLUDE_DIR})

target_link_libraries(eggs-bin eggs dl ${SDL2_LIBRARY} ${SDL2TTFMAIN_LIBRARY} ${SDL2IMAGE_LIBRARY})
set_target_properties(eggs-bin PROPERTIES OUTPUT_NAME eggs)

set(CMAKE_CXX_FLAGS "-std=c++11")
