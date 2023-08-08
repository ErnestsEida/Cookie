#pragma once
#include "interfaces/IDisplayWindow.cpp"

class ScriptEditor : public IDisplayWindow {
public:
  void create() override {
    if (this->is_open) {
      ImGui::Begin("Scripts Editor", &this->is_open);
      ImGui::End();
    }
  }
};