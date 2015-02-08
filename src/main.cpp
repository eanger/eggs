#include <iostream>
#include <chrono>
#include <cassert>
#include <dlfcn.h>

#include "utils/easylogging++.h"

#include "input.h"
#include "screen.h"
#include "assets.h"

using namespace std;
using namespace std::chrono;
using namespace eggs;

_INITIALIZE_EASYLOGGINGPP

namespace {

int checked_dlclose(void* handle){
  if(handle){
    return dlclose(handle);
  }
  return 0;
}

unique_ptr<void, int (*)(void*)> get_library_handle() {
  unique_ptr<void,int(*)(void*)> handle{nullptr, checked_dlclose};

  auto orig_lib = get_lib_path("libeggs.so");
  auto live_lib = get_lib_path("libeggs-live.so");

  stringstream sys_call;
  sys_call << "cp " << orig_lib << " " << live_lib;
  system(sys_call.str().c_str());
  LOG(INFO) << "Reloading library";
  handle.reset(dlopen(live_lib.c_str(), RTLD_LAZY));
  if (!handle) {
    LOG(FATAL) << "Unable to open library: " << dlerror();
    throw runtime_error("Unable to open library");
  }
  return move(handle);
}

template<typename T>
T get_symbol(const char* name, void* handle){
  T result = (T) dlsym(handle, name);
  if(!result){
    LOG(FATAL) << "Unable to load symbol: " << dlerror();
    throw runtime_error("Unable to load symbol");
  }
  return result;
}

} // end unnamed namespace

int main(int argc, char* argv[]){
  _START_EASYLOGGINGPP(argc, argv);
  time_point<system_clock> last_reload_time;
  typedef void (*update_t)(State*);
  update_t update;
  unique_ptr<void,int(*)(void*)> handle{nullptr, checked_dlclose};

  Screen screen;
  State state{screen.get_renderer()};
  while(!state.done){
    auto elapsed = system_clock::now() - last_reload_time;
    if(elapsed > seconds(5)){
      handle.reset(nullptr);
      handle = get_library_handle();
      update = get_symbol<update_t>("update", handle.get());
      last_reload_time = system_clock::now();
    }
    assert(update && "Did not successfully load symbol");
  
    read_input(state);
    update(&state);
    screen.update(state);
  }
  
  LOG(INFO) << "Successful exit, quitting";
}

