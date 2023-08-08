#pragma once
#include <iostream>
#include "imgui.h"
#include "index_windows.cpp"
#include "globals/windows_manager.cpp"

class MainMenuBar {
private:
public:
  void create() {
    if (ImGui::BeginMainMenuBar())
    {
      if (ImGui::BeginMenu("Windows")) // Project tab
      {
        if (ImGui::MenuItem("GameObject Builder")) {
          WindowsManager::all_windows.push_back(new GameObjectBuilder());
        }

        if (ImGui::MenuItem("GameRoom Builder")) {
          WindowsManager::all_windows.push_back(new GameRoomBuilder());
        }

        if (ImGui::MenuItem("Script Editor")) {
          WindowsManager::all_windows.push_back(new ScriptEditor());
        }

        if (ImGui::MenuItem("Assets Manager")) {
          WindowsManager::all_windows.push_back(new AssetsManager());
        }
        ImGui::EndMenu();
      }
      ImGui::EndMainMenuBar();
    }
  }
};
