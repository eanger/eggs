#include <iostream>

#include "utils/easylogging++.h"
#include "engine.h"

using namespace std;

_INITIALIZE_EASYLOGGINGPP

int main(int argc, char* argv[]){
  _START_EASYLOGGINGPP(argc, argv);
  cout << "Hello, world!" << endl;
  eggs::start_engine();
}

