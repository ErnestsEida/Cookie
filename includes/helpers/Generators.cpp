#pragma once

#include <iostream>
#include <chrono>

using namespace std;

namespace Generators {
  string MakeUniqID(string prefix = "") {
    uint64_t millisec = chrono::system_clock::now().time_since_epoch().count();
    string timeAsString = to_string(millisec);
    return prefix + timeAsString;
  }
};