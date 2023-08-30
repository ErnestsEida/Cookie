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

  float child_size[2] = { 0, 0 };
  float child_offset[2] = { 0, 0 };
  float child_node_offset[3] = { 0, 0, 0 };

  // ============================================== MISCELANEOUS =====================================================

  // Just reset all child placeholder values to zero (0); The amounts are so small that i dont see the need for a loop
  void ResetChildVariables() {
    child_offset[0] = 0;
    child_offset[1] = 0;
    child_size[0] = 0;
    child_size[1] = 0;
    child_node_offset[0] = 0;
    child_node_offset[1] = 0;
    child_node_offset[2] = 0;
  }

  bool RemoveScriptFromObject(ScriptModel* script) {
    for(size_t i = 0; i < selected_object->script_ids.size(); i++) {
      if (selected_object->script_ids.at(i) == script->id) {
        selected_object->script_ids.erase(selected_object->script_ids.begin() + i);
        selected_object->script_ids.shrink_to_fit();
        return true;
      }
    }
    return false;
  }

  vector<ScriptModel*> GetCurrentGameobjectScripts() {
    vector<ScriptModel*> all_scripts = ModelStorage::scripts;
    vector<ScriptModel*> result;

    for(size_t i = 0; i < all_scripts.size(); i++) {
      ScriptModel* script = all_scripts.at(i);
      if (result.size() == selected_object->script_ids.size()) break; // No need to iterate through vectors, if there are no scripts added

      for(size_t u = 0; selected_object->script_ids.size(); u++) {
        if (selected_object->script_ids.at(u) == script->id) {
          result.push_back(script);
          break;
        }
      }
    }

    return result;
  }

  vector<GameObjectChild> GetChildrenByType(GameObjectChildType type) {
    vector<GameObjectChild> parsed_children;
    for(size_t i = 0; i < selected_object->children.size(); i++) {
      GameObjectChild child = selected_object->children.at(i);
      if (child.type == type) parsed_children.push_back(child);
    }
    return parsed_children;
  }

  // Basically we give back all gameobjects EXCEPT for currently selected
  vector<GameObjectModel*> SelectableGameObjects() {
    vector<GameObjectModel*> result;
    for(size_t i = 0; i < ModelStorage::gameobjects.size(); i++) {
      if (ModelStorage::gameobjects.at(i)->id != selected_object->id) result.push_back(ModelStorage::gameobjects.at(i));
    }
    return result;
  }

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

  void ShowSpriteRendererModal()
  {
    ImGuiWindowFlags flags = ImGuiWindowFlags_AlwaysAutoResize;
    flags |= ImGuiWindowFlags_NoMove;
    if (ImGui::BeginPopupModal("Add SpriteRenderer", NULL, flags)) 
    {

      ImGui::Text("Preset shapes");
      if (ImGui::BeginListBox("## Preset Selection", ImVec2(300, 40))) 
      {
        if (ImGui::Selectable("Circle")) {}
        if (ImGui::Selectable("Rectangle")) {}
        ImGui::EndListBox();
      }

      ImGui::Text("Animations");
      if (ImGui::BeginListBox("## Animation Selection", ImVec2(300, 80)))
      {
        // Load animations
        // ...
        // else if no animations are present
        string empty_text = "No animations were found...";
        auto windowWidth = ImGui::GetWindowSize().x;
        auto textWidth   = ImGui::CalcTextSize(empty_text.c_str()).x;
        ImGui::SetCursorPosX((windowWidth - textWidth) * 0.5f);
        ImGui::Text(empty_text.c_str());

        ImGui::EndListBox();
      }

      if (ImGui::Button("Accept", ImVec2(300, 30))) ImGui::CloseCurrentPopup();
      if (ImGui::Button("Cancel", ImVec2(300, 30))) ImGui::CloseCurrentPopup();
      ImGui::EndPopup();
    }
  }

  void ShowColliderModal()
  {
    ImGuiWindowFlags flags = ImGuiWindowFlags_AlwaysAutoResize;
    flags |= ImGuiWindowFlags_NoMove;
    if (ImGui::BeginPopupModal("Add Collider", NULL, flags)) 
    {
      ImGui::InputFloat2("Size (X, Y)", child_size, "%.2f");
      ImGui::InputFloat2("Offset (X, Y)", child_offset, "%.2f");

      if (ImGui::Button("Accept", ImVec2(300, 30)))
      {
        GOC_ColliderData collider_data(ImVec2(child_size[0], child_size[1]), ImVec2(child_offset[0], child_offset[1]));
        GameObjectChild new_child(collider_data);
        selected_object->children.push_back(new_child);
        ResetChildVariables();
        ImGui::CloseCurrentPopup();
      }
      if (ImGui::Button("Cancel", ImVec2(300, 30))) ImGui::CloseCurrentPopup();
      ImGui::EndPopup();
    }
  }

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
            selected_object->script_ids.push_back(script->id);
            ImGui::CloseCurrentPopup();
          }
        }
        ImGui::EndListBox();  
      }

      if (ImGui::Button("Cancel", ImVec2(400, 30))) ImGui::CloseCurrentPopup();
      ImGui::EndPopup();
    }
  }

  void ShowChildSelectModal()
  {
    ImGuiWindowFlags flags = ImGuiWindowFlags_AlwaysAutoResize;
    flags |= ImGuiWindowFlags_NoMove;
    if (ImGui::BeginPopupModal("GameObject List", NULL, flags)) 
    {
      ImGui::InputFloat3("Offset[X Y Z]", child_node_offset, "%.2f");
      if (ImGui::BeginListBox("##node_select_list", ImVec2(400, 550)))
      {
        vector<GameObjectModel*> gameobjects = SelectableGameObjects();
        for(size_t i = 0; i < gameobjects.size(); i++) {
          GameObjectModel* gameobject = gameobjects.at(i);
          if (ImGui::Selectable(gameobject->name.c_str()))
          { 
            GOC_NodeData node_data(gameobject->id, child_node_offset);
            GameObjectChild new_child(node_data);
            selected_object->children.push_back(new_child);
            ResetChildVariables();
            ImGui::CloseCurrentPopup();
          }
        }
        ImGui::EndListBox();  
      }

      if (ImGui::Button("Cancel", ImVec2(400, 30))) ImGui::CloseCurrentPopup();
      ImGui::EndPopup();
    }
  }

  // ================================== COMPONENTS ==================================

  void ShowComponentSelectionWindow()
  {
    if (ImGui::BeginPopupContextItem("add_component_context"))
    {
      if (ImGui::Button("New SpriteRenderer")) ImGui::OpenPopup("Add SpriteRenderer");
      ShowSpriteRendererModal();
      if (ImGui::Button("New Collider")) ImGui::OpenPopup("Add Collider");
      ShowColliderModal();
      if (ImGui::Button("New Script")) ImGui::OpenPopup("Script List");
      ShowScriptSelectModal();
      if (ImGui::Button("New Child")) ImGui::OpenPopup("GameObject List");
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

  void ShowDetailsChildTree() {
    vector<ScriptModel*> scripts_for_object = GetCurrentGameobjectScripts();
    string scripts_header = "Scripts (" + to_string(scripts_for_object.size()) +  ")";
    if (ImGui::TreeNode(scripts_header.c_str()))
    {
      for(size_t i = 0; i < scripts_for_object.size(); i++) {
        ScriptModel* current_script = scripts_for_object.at(i);
        if (ImGui::CollapsingHeader(current_script->name.c_str()))
        {
          ImVec2 space = ImGui::GetContentRegionAvail();
          if (ImGui::Button("Edit", ImVec2(space.x / 2, 25))) {}
          ImGui::SameLine();
          if (ImGui::Button("Remove", ImVec2(space.x / 2, 25))) RemoveScriptFromObject(current_script);
        }
      }
      ImGui::TreePop();
    }
    vector<GameObjectChild> node_children = GetChildrenByType(GameObjectChildType::Node);
    vector<GameObjectChild> collider_chidren = GetChildrenByType(GameObjectChildType::Collider);
    vector<GameObjectChild> renderer_children = GetChildrenByType(GameObjectChildType::SpriteRenderer);
  }

  void ShowGameObjectDetails()
  {
    ImGui::SameLine();
    ImVec2 avail_space = ImGui::GetContentRegionAvail();
    ImGui::BeginChild("##Gameobject_details", ImVec2(400, avail_space.y), true);
      if (selected_object != nullptr)
      {
        string complete_text = "Selected --> [ " + selected_object->name + " ]";
        ImGui::Text(complete_text.c_str());

        ShowDetailsChildTree();

        ShowComponentSelectionWindow();
        if (ImGui::Button("Add [+]", ImVec2(400, 40))) {
          ImGui::OpenPopup("add_component_context");
        }
      }
      else 
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