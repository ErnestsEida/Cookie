#pragma once
#include "../imgui/imgui.h"

class IDisplayWindow {
protected:
  bool is_open = true;
public:
  void close() {
    is_open = false;
  }

  virtual void create() = 0; 
};