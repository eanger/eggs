cmake_minimum_required (VERSION 2.8.11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
project(eggs)

set(CMAKE_PREFIX_PATH "C:/Users/Eric/Downloads/SFML-2.1-windows-gcc-4.7-mingw-32bits/SFML-2.1")
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})
find_package(SFML 2.1 REQUIRED system window graphics)
add_subdirectory(src)
