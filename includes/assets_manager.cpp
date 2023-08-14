#pragma once
#include "interfaces/IDisplayWindow.cpp"

typedef struct {
  short r,g,b,a;
} RGBA;

class AssetsManager : public IDisplayWindow {
private:
  float color[4];
  bool sizeWasSet = false;
  bool drawing = false;
  
  const int assetWidth = 256;
  const int assetHeight = 256;

  unsigned char assetPixels[256 * 256 * 3];

  ////////////////////////////// COMPONENTS /////////////////////////////

  void ShowDrawingControls() {
    ImGuiColorEditFlags color_picker_flags = ImGuiColorEditFlags_DisplayRGB;
    color_picker_flags |= ImGuiColorEditFlags_NoSidePreview;
    ImVec2 space_avail = ImGui::GetContentRegionAvail();

    ImGui::BeginChild("##asset_manager_left_side_wrapper", ImVec2(245, space_avail.y), true);
      if (ImGui::Button("Save Asset", ImVec2(225, 40))) {
        // Save asset
      }

      if (ImGui::Button("New Asset", ImVec2(225, 40))) {
        // New Asset
      }
      
      ImGui::BeginChild("##asset_manager_color_window", ImVec2(350, 300));
        ImGui::ColorPicker4("##asset_manager_color_picker", color, color_picker_flags);
      ImGui::EndChild();
    ImGui::EndChild();
  }

  void ShowDrawingArea() {
    ImGui::SameLine();
    ImVec2 space = ImGui::GetContentRegionAvail();

    ImGui::BeginChild("##DrawingArea", space, true);
      ImGui::Image(reinterpret_cast<void*>(assetPixels), ImVec2(assetWidth, assetHeight));     
      ImGuiIO& io = ImGui::GetIO();
    ImGui::EndChild();
  }

  void ShowAssetInspector() {
    ImVec2 avail_space = ImGui::GetContentRegionAvail();
    if (ImGui::BeginListBox("##asset_manager_inspector", ImVec2(300, avail_space.y))) {   
      ImGui::EndListBox();
    }
  }

public:
  void create() override {
    if (!sizeWasSet) {
      ImGui::SetNextWindowSize(ImVec2(720, 480));
      sizeWasSet = true;
    }

    if (this->is_open) {
      ImGui::Begin("Assets Manager", &this->is_open);
        ShowDrawingControls();
        ShowDrawingArea(); 
        // ShowAssetInspector();
      ImGui::End();
    }
  }
};