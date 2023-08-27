#pragma once
#include "interfaces/IDisplayWindow.cpp"
#include "globals/model_storage.cpp"

struct NewGameobjectFields {
  char name[64] = "";
  float coords[3] = {0, 0, 0};
};

class GameObjectBuilder : public IDisplayWindow {
private:
  bool size_was_set = false;
  NewGameobjectFields new_fields;

  bool InvokeNewGameObject()
  {

  }

  void ShowNewGameObjectForm() {
    if (ImGui::BeginPopupModal("New GameObject Form", NULL, ImGuiWindowFlags_NoResize))
    {
      ImGui::InputText("Name", new_fields.name, 64);
      ImGui::InputFloat3("[x|y|z]", new_fields.coords);
      if (ImGui::Button("Accept", ImVec2(115, 30)))
      {
        if (InvokeNewGameObject()) ImGui::CloseCurrentPopup();
      }
      ImGui::SameLine();
      if (ImGui::Button("Cancel", ImVec2(115, 30))) ImGui::CloseCurrentPopup();
      ImGui::EndPopup();
    }
  }

  void ShowGameObjectControls() 
  {
    if (ImGui::Button("Create", ImVec2(115, 30))) ImGui::OpenPopup("New GameObject Form");
    ShowNewGameObjectForm();
  }

  void ShowGameObjectInspector()
  {
    ImVec2 avail_space = ImGui::GetContentRegionAvail();
    ImGui::BeginChild("##GameObject Index", ImVec2(250, avail_space.y), true);
      ShowGameObjectControls();
      ImGui::Text("GameObject Index");
      avail_space = ImGui::GetContentRegionAvail();
      if (ImGui::BeginListBox("##gameobject_inspector_list", avail_space))
      {
        for(size_t i = 0; i < ModelStorage::gameobjects.size(); i++) 
        {
          GameObjectModel* gameobject = ModelStorage::gameobjects.at(i);
          if (ImGui::Selectable(gameobject->name.c_str())) {}
        }
        ImGui::EndListBox();
      }
    ImGui::EndChild();
  }

  void ShowGameObjectWorkarea()
  {
    ImGui::SameLine();
    ImVec2 avail_space = ImGui::GetContentRegionAvail();
    ImGui::BeginChild("##Gameobject_workarea", ImVec2(avail_space.x - 415, avail_space.y), true);
    ImGui::Text("Workarea");
    ImGui::EndChild();
  }

  void ShowGameObjectDetails()
  {
    ImGui::SameLine();
    ImVec2 avail_space = ImGui::GetContentRegionAvail();
    ImGui::BeginChild("##Gameobject_details", ImVec2(400, avail_space.y), true);
      ImGui::Text("Details");
    ImGui::EndChild();
  }

public:
  void create() override
  {
    if (this->is_open)
    {
      if (!size_was_set)
      {
        ImGui::SetNextWindowSize(ImVec2(720, 480));
        size_was_set = true;
      }

      ImGui::Begin("GameObject Builder", &this->is_open);
        ShowGameObjectInspector();
        ShowGameObjectWorkarea();
        ShowGameObjectDetails();
      ImGui::End();
    }
  }
};