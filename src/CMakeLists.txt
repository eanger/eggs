file(GLOB_RECURSE INCS "*.h")
add_executable(eggs
engine.cpp
input.cpp
main.cpp
screen.cpp
state.cpp
world.cpp
timer.cpp
event_queue.cpp
${INCS})

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})
find_package(SDL2 REQUIRED)
find_package(SDL2TTF REQUIRED)
find_package(SDL2IMAGE REQUIRED)

include_directories(${SDL2_INCLUDE_DIR} ${SDL2TTF_INCLUDE_DIR} ${SDL2IMAGE_INCLUDE_DIR})
target_link_libraries(eggs ${SDL2_LIBRARY} ${SDL2TTFMAIN_LIBRARY} ${SDL2IMAGE_LIBRARY})

add_definitions(-DBINDIR="${CMAKE_CURRENT_BINARY_DIR}")
