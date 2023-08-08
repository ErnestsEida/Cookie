#pragma once

#include <iostream>
#include <chrono>

using namespace std;

class Generator {
public:
  static string GenerateID() {
    uint64_t millisec = chrono::system_clock::now().time_since_epoch().count();
    return to_string(millisec);
  }
};