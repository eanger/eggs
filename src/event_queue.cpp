#include <chrono>
#include <cassert>

#include "utils/easylogging++.h"
#include "event_queue.h"

using namespace std::chrono;

namespace eggs {

EventQueue::Event::Event(std::function<void(void)> callback,
                  steady_clock::time_point deadline) :
  callback_{callback}, deadline_{deadline} {}

void EventQueue::make_call_in(std::function<void(void)> func,
                              double secs){
  assert(secs > 0 && "Can't make a call in the past");
  auto deadline = steady_clock::now();
  deadline += duration_cast<steady_clock::duration>(duration<double>{secs});
  queue_.push(Event{func, deadline});
}

void EventQueue::update() {
  auto now = steady_clock::now();
  while(!queue_.empty() &&
        queue_.top().deadline_ < now){
    queue_.top().callback_();
    queue_.pop();
  }
}

}

