#pragma once

#include <chrono>

namespace eggs{
class Timer {
  public:
    void start();
    void stop();
    double read_ms() const;
    void reset();
  private:
    std::chrono::time_point<std::chrono::high_resolution_clock> start_;
    std::chrono::duration<double,std::milli> elapsed_;
};
}
