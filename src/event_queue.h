#pragma once

#include <queue>
#include <functional>
#include <chrono>

namespace eggs {

class EventQueue {
  public:
    void make_call_in(std::function<void(void)> func, double secs);
    void update();
  private:
    struct Event {
      Event(std::function<void(void)> callback,
            std::chrono::steady_clock::time_point deadline);
      friend bool operator>(const Event& lhs, const Event& rhs);

      std::function<void(void)> callback_;
      std::chrono::steady_clock::time_point deadline_;
    };
    friend bool operator>(const Event& lhs, const Event& rhs);

    std::priority_queue<Event, std::vector<Event>, std::greater<Event>> queue_;

};

inline bool operator>(const EventQueue::Event& lhs, const EventQueue::Event& rhs){
  return lhs.deadline_ > rhs.deadline_;
}
}
