#pragma once
#include "interfaces/IDisplayWindow.cpp"
#include "globals/model_storage.cpp"
#include "helpers/names.cpp"

struct NewGameobjectFields {
  char name[64] = "";
  float coords[2] = {0, 0};
  int z_index = 0;
};

class GameObjectBuilder : public IDisplayWindow {
private:
  bool size_was_set = false;
  NewGameobjectFields new_fields;
  GameObjectModel* selected_object = nullptr;

  // ============================================== MISCELANEOUS =====================================================

  bool isSelected(GameObjectModel* gameobject) {
    if (selected_object != nullptr) {
      return gameobject->id == selected_object->id;
    }
    return false;
  }

  bool InvokeNewGameObject()
  {
    string name_as_str = processName(string(new_fields.name));
    if (name_as_str.length() == 0) return false;

    GameObjectModel* new_gameobject = new GameObjectModel(name_as_str, new_fields.coords[0], new_fields.coords[1], new_fields.z_index);
    return ModelStorage::InsertGameObject(new_gameobject);
  }

  // ============================================== SELECTION/CREATION MODALS =================================================

  void ShowSpriteRendererModal() {}

  void ShowColliderModal() {}

  void ShowScriptSelectModal()
  {
    ImGuiWindowFlags flags = ImGuiWindowFlags_AlwaysAutoResize;
    flags |= ImGuiWindowFlags_NoMove;
    if (ImGui::BeginPopupModal("Script List", NULL, flags)) 
    {
      ImVec2 avail = ImGui::GetContentRegionAvail();
      if (ImGui::BeginListBox("##script_select_list", ImVec2(400, 550)))
      {
        for(size_t i = 0; i < ModelStorage::scripts.size(); i++) {
          ScriptModel* script = ModelStorage::scripts.at(i);
          if (ImGui::Selectable(script->name.c_str()))
          {
            ImGui::CloseCurrentPopup();
          }
        }
        ImGui::EndListBox();  
      }

      if (ImGui::Button("Cancel", ImVec2(400, 30))) ImGui::CloseCurrentPopup();
      ImGui::EndPopup();
    }
  }

  void ShowChildSelectModal() {}

  // ================================== COMPONENTS ==================================

  void ShowComponentSelectionWindow()
  {
    if (ImGui::BeginPopupContextItem("add_component_context"))
    {
      if (ImGui::Button("New SpriteRenderer")) {}
      ShowSpriteRendererModal();
      if (ImGui::Button("New Collider")) {}
      ShowColliderModal();
      if (ImGui::Button("New Script")) ImGui::OpenPopup("Script List");
      ShowScriptSelectModal();
      if (ImGui::Button("New Child")) {}
      ShowChildSelectModal();
      ImGui::EndPopup();
    }
  }

  void ShowNewGameObjectForm() {
    if (ImGui::BeginPopupModal("New GameObject Form", NULL, ImGuiWindowFlags_NoResize))
    {
      ImGui::InputText("name", new_fields.name, 64);
      ImGui::InputFloat2("[x|y]", new_fields.coords, "%.2f");
      ImGui::InputInt("z-index", &new_fields.z_index, 1, 100);
      if (ImGui::Button("Accept", ImVec2(115, 30)))
      {
        if (InvokeNewGameObject()) 
        {
          new_fields = NewGameobjectFields();
          ImGui::CloseCurrentPopup();
        }
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
          if (ImGui::Selectable(gameobject->name.c_str(), isSelected(gameobject))) selected_object = gameobject;
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
    ImGui::EndChild();
  }

  void ShowGameObjectDetails()
  {
    ImGui::SameLine();
    ImVec2 avail_space = ImGui::GetContentRegionAvail();
    ImGui::BeginChild("##Gameobject_details", ImVec2(400, avail_space.y), true);
      ShowSpriteRendererModal();
      ShowColliderModal();
      ShowScriptSelectModal();
      ShowChildSelectModal();
      if (selected_object != nullptr)
      {
        string complete_text = "Selected --> [ " + selected_object->name + " ]";
        ImGui::Text(complete_text.c_str());

        ShowComponentSelectionWindow();
        if (ImGui::Button("Add [+]", ImVec2(400, 40))) {
          ImGui::OpenPopup("add_component_context");
        }
      } else 
      {
        ImGui::Text("No GameObject is currently selected...");
      }
    ImGui::EndChild();
  }

// ======================================================================================================
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