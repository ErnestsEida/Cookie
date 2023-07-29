#pragma once
#include "imgui/imgui.h"

class Test {
public:
  static bool isOpen;

  static void Create() {
    if (isOpen) {
      ImGui::Begin("Test Window", &isOpen);
      ImGui::End();
    }
  }
};

bool Test::isOpen = true;