add_executable(eggs
engine.cpp
input.cpp
main.cpp
screen.cpp
state.cpp
world.cpp)

include_directories(${SFML_INCLUDE_DIR})
target_link_libraries(eggs ${SFML_LIBRARIES})
