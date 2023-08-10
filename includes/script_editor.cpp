#pragma once
#include <iostream>
#include <vector>
#include "imgui/imgui.h"
#include "TextEditor.h"
#include "interfaces/IDisplayWindow.cpp"
#include "data_structures/ScriptModel.cpp"
#include "globals/model_storage.cpp"

using namespace std;

class ScriptEditor : public IDisplayWindow {
private:
  char new_script_name[64] = "";
  bool sizeWasSet = false;
  TextEditor* editor = nullptr;
  ScriptModel* selected = nullptr;

  // SETUP || OTHER
  void SetupEditor() {
    this->editor = new TextEditor();
    this->editor->SetTabSize(2);
    this->editor->SetShowWhitespaces(false);
  }

  ImGuiWindowFlags getMainWindowFlags() {
    ImGuiWindowFlags flags = ImGuiWindowFlags_MenuBar;
    return flags;
  }

  const char* getWindowName() {
    string window_name = isSelectedPresent() ? ("Script Editor - " + this->selected->name) : "Script Editor";
    return window_name.c_str();
  }

  bool InvokeCreateNewScript() {
    string script_name_as_str = string(this->new_script_name);
    if (script_name_as_str.size() == 0) return false;

    ScriptModel* newScript = new ScriptModel(script_name_as_str);
    bool result = ModelStorage::InsertScript(newScript);
    return result;
  }

  // ===============

  // SUB-COMPONENTS
  void ShowNewScriptModal() {

    if (ImGui::BeginPopupModal("New script form", NULL, ImGuiWindowFlags_NoResize)) {
      ImGui::InputText("name", this->new_script_name, 64);

      if (ImGui::Button("Accept", ImVec2(130, 30))) {
        if (InvokeCreateNewScript()) memset(this->new_script_name, '\0', 64);
      }
      ImGui::SameLine();
      if (ImGui::Button("Cancel", ImVec2(130, 30))) {
        ImGui::CloseCurrentPopup();
      }
      ImGui::EndPopup();
    }
  }

  void ShowUserActions() {
    if (ImGui::Button("New script", ImVec2(130, 30))) {
      ImGui::OpenPopup("New script form");
    }

    ImGui::SameLine();
    if (ImGui::Button("Save", ImVec2(130, 30))) {

    }
    
    string current_script_text = isSelectedPresent() ? "Editing: " + this->selected->name : "";
    ImGui::SameLine();
    ImGui::Text(current_script_text.c_str());
  }

  void ShowScriptInspector() {
    int available_height = ImGui::GetContentRegionAvail().y;

    if (ImGui::BeginListBox("##Script inspector", ImVec2(200, available_height))) {
      for(size_t i = 0;i < ModelStorage::scripts.size(); i++) {
        ScriptModel* script = ModelStorage::scripts.at(i);
        if (ImGui::Selectable(script->name.c_str())) {
          SelectScript(script);
        }
      }
      ImGui::EndListBox();
    }
  }

  void ShowScriptEditor() {
    ImVec2 avail = ImGui::GetContentRegionAvail();
    ImGui::BeginChild("##Editor", avail, true);
      this->editor->SetReadOnly(!this->isSelectedPresent());
      this->editor->Render("Testing");
    ImGui::EndChild();
  }
  // ==================

public: //////////////////////////////////////////////////////////////////// PUBLIC //////////////////////////////////////////////////////////
  ScriptEditor() {
    this->editor = new TextEditor();
    this->SetupEditor();
  }

  void SelectScript(ScriptModel* script) {
    if (isSelectedPresent()) {
      this->selected->content = this->editor->GetText();
    }
    this->selected = script;
    this->editor->SetText(script->content);
  }

  bool isSelectedPresent() {
    return this->selected != nullptr;
  }

  ////////////////// MAIN CREATE ////////////////////
  void create() override {
    if (this->is_open) {
      ImGuiWindowFlags flags = getMainWindowFlags();
      if (!this->sizeWasSet) { 
        ImGui::SetNextWindowSize(ImVec2(720, 480));
        this->sizeWasSet = true;
      }

      ImGui::Begin("Script Editor", &this->is_open, flags);   
        
        ShowUserActions();
        ShowScriptInspector();
        ImGui::SameLine();
        ShowScriptEditor();

        ShowNewScriptModal();

      ImGui::End();
    } else {
      this->sizeWasSet = false;
    }
  }
};