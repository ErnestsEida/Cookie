#pragma once
#include "interfaces/IDisplayWindow.cpp"

class GameObjectBuilder : public IDisplayWindow {
  void create () override {
    if (this->is_open) {
      ImGui::Begin("GameObject Builder", &this->is_open);
      ImGui::End();
    }
  }
};