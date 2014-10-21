add_executable(eggs
engine.cpp
input.cpp
main.cpp
screen.cpp
state.cpp
world.cpp)

#set(CMAKE_PREFIX_PATH "C:/Users/Eric/Downloads/SFML-2.1-windows-gcc-4.7-mingw-32bits/SFML-2.1")
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})
find_package(SDL2 REQUIRED)
find_package(SDL2TTF REQUIRED)

include_directories(${SDL2_INCLUDE_DIR} ${SDL2TTF_INCLUDE_DIR})
target_link_libraries(eggs ${SDL2_LIBRARY} ${SDL2TTFMAIN_LIBRARY})

add_definitions(-DBINDIR="${CMAKE_CURRENT_BINARY_DIR}")
