#include "imgui.h"
#include <iostream>

class MainMenuBar {
public:
  static void create() {
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("Project")) // Project tab
        {
            if (ImGui::MenuItem("New")) { // New Project
            }

            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
  }
};
