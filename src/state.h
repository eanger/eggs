#pragma once

namespace eggs{
class State{
  private:
    virtual void do_update(int key_pressed) = 0;
  public:
    void update(int key_pressed);
    virtual ~State();
};
}
