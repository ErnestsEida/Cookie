#pragma once
#include "interfaces/IDisplayWindow.cpp"
#include <iostream>
#include <vector>

using namespace std;

class AssetsManager : public IDisplayWindow {
private:
  float color[4] = { 255, 255, 255, 1 };
  bool draw_area_set = false;

  ////////////////////////////// COMPONENTS /////////////////////////////

  void ShowDrawingControls() {
    ImGuiColorEditFlags color_picker_flags = ImGuiColorEditFlags_DisplayRGB;
    color_picker_flags |= ImGuiColorEditFlags_NoSidePreview;

    ImGui::Begin("Canvas controls", &this->is_open);
      if (ImGui::Button("Save Asset", ImVec2(225, 40))) {
        // Save asset
      }

      if (ImGui::Button("New Asset", ImVec2(225, 40))) {
        // New Asset
      }
      
      ImGui::BeginChild("##asset_manager_color_window", ImVec2(350, 300));
        ImGui::ColorPicker4("##asset_manager_color_picker", color, color_picker_flags);
      ImGui::EndChild();
    ImGui::End();
  }

  void ShowDrawingArea() {
    if (!this->draw_area_set) {
      ImGui::SetNextWindowSize(ImVec2(720, 480));
      this->draw_area_set = true;
    }

    ImGui::Begin("Asset Canvas", &this->is_open);
      ImVec2 drawListSize = ImGui::GetContentRegionAvail();
      ImVec2 canvas_pos = ImGui::GetCursorScreenPos();  
      ImDrawList* draw_list = ImGui::GetWindowDrawList();

      ImGui::InvisibleButton("##Canvas", drawListSize);
      if (ImGui::IsItemHovered) {
        ImVec2 mouse_pos_in_canvas = ImVec2(ImGui::GetIO().MousePos.x - canvas_pos.x, ImGui::GetIO().MousePos.y - canvas_pos.y);
        // This would be the main drawing loop. Might need to delegate to functions since there is a lot of logic to handle.
      }

    ImGui::End();
  }

public:
  void create() override {
    if (this->is_open) {
      ShowDrawingControls();
      ShowDrawingArea();
    }
  }
};