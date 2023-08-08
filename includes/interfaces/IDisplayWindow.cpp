#pragma once
#include "../imgui/imgui.h"

class IDisplayWindow {
public:
  bool is_open = true;

  void close() {
    is_open = false;
  }

  void open() {
    is_open = true;
  }

  virtual void create() = 0; 
};