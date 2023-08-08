#pragma once
#include <iostream>
#include "imgui/imgui.h"
#include "index_windows.cpp"
#include "globals/windows_manager.cpp"

class MainMenuBar {
private:
  void WindowsSelection() {
    if (ImGui::BeginMenu("Windows")) // Project tab
      {
        if (ImGui::MenuItem("GameObject Builder")) {
          if (WindowsManager::gameobject_builder_window == nullptr) {
            WindowsManager::gameobject_builder_window = new GameObjectBuilder();
          } else {
            WindowsManager::gameobject_builder_window->open();
          }
        }

        if (ImGui::MenuItem("GameRoom Builder")) {
          if (WindowsManager::gameroom_builder_window == nullptr) {
            WindowsManager::gameroom_builder_window = new GameRoomBuilder();
          } else {
            WindowsManager::gameroom_builder_window->open();
          }
        }

        if (ImGui::MenuItem("Script Editor")) {
          if (WindowsManager::script_editor_window == nullptr) {
            WindowsManager::script_editor_window = new ScriptEditor();
          } else {
            WindowsManager::script_editor_window->open();
          }
        }

        if (ImGui::MenuItem("Assets Manager")) {
          if (WindowsManager::assets_manager_window == nullptr) {
            WindowsManager::assets_manager_window = new AssetsManager();
          } else {
            WindowsManager::assets_manager_window->open();
          }
        }

        ImGui::EndMenu();
      }
  }
  
public:
  void create() {
    if (ImGui::BeginMainMenuBar())
    {
      WindowsSelection();
      ImGui::EndMainMenuBar();
    }
  }
};
