#ifndef ENGINE_H
#define ENGINE_H

namespace eggs{
enum class State;
int start_engine();
void update(State& state, uint32_t elapsed_ms);
}

#endif // ENGINE_H
