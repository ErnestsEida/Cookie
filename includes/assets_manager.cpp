#pragma once
#include "interfaces/IDisplayWindow.cpp"

class AssetsManager : public IDisplayWindow {
public:
  void create() override {
    if (this->is_open) {
      ImGui::Begin("Assets Manager", &this->is_open);
      ImGui::End();
    }
  }
};