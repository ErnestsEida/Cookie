#pragma once
#include "imgui/imgui.h"
#include "interfaces/IDisplayWindow.cpp"
#include <iostream>
#include <vector>

using namespace std;

class ScriptEditor : public IDisplayWindow {
private:
  int bufferSize = 4096;
  char* input = nullptr;

  string transform_input() {
    return string(this->input);
  }

public:
  ScriptEditor() {
    this->input = new char[this->bufferSize];
  }

  void create() override {
    if (this->is_open) {
      ImGui::Begin("Scripts Editor", &this->is_open, ImGuiWindowFlags_NoResize);

      ImGui::InputTextMultiline("##ScriptEditor", this->input, this->bufferSize, ImVec2(720, 480), ImGuiInputTextFlags_AllowTabInput);

      ImGui::End();
    }
  }
};