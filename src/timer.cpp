#include <chrono>

#include "timer.h"

using namespace std;

namespace eggs{

void Timer::start() {
  start_ = chrono::high_resolution_clock::now();
}

void Timer::stop() {
  auto end_ = chrono::high_resolution_clock::now();
  elapsed_ += end_ - start_;
}

double Timer::read_ms() const {
  return elapsed_.count();
}

void Timer::reset() {
  elapsed_ = chrono::duration<double,std::milli>::zero();
}

}

