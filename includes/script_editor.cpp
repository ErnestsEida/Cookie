#pragma once
#include <iostream>
#include <vector>
#include "imgui/imgui.h"
#include "TextEditor.h"
#include "interfaces/IDisplayWindow.cpp"
#include "data_structures/ScriptModel.cpp"

using namespace std;

class ScriptEditor : public IDisplayWindow {
private:
  TextEditor* editor = nullptr;
  ScriptModel* selected = nullptr;

  void SetupEditor() {
    this->editor = new TextEditor();
    this->editor->SetTabSize(2);
  }

  ImGuiWindowFlags getMainWindowFlags() {
    ImGuiWindowFlags flags = ImGuiWindowFlags_NoResize;
    flags |= ImGuiWindowFlags_MenuBar;
    return flags;
  }

public:
  ScriptEditor() {
    this->editor = new TextEditor();
    this->SetupEditor();
  }

  void SelectScript(ScriptModel* script) {
    this->selected = script;
  }

  void create() override {
    if (this->is_open) {
      ImGuiWindowFlags flags = getMainWindowFlags();
      ImGui::Begin("Scripts Editor", &this->is_open, flags);
      MakeMenuBar();
      

      this->editor->SetReadOnly(this->selected == nullptr);
      this->editor->Render("Testing", ImVec2(720, 480), true);

      ImGui::End();
    }
  }
};