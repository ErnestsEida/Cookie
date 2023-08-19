#pragma once
#include "interfaces/IDisplayWindow.cpp"
#include "helpers/AssetManagerIndex.cpp"
#include "helpers/names.cpp"
#include "globals/model_storage.cpp"
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

struct AssetModalFields {
  char name[64] = "";
  int size_x = 0;
  int size_y = 0;
};

class AssetsManager : public IDisplayWindow {
private:
  bool draw_area_set = false;
  bool is_drawing = false;
  bool is_new_modal_open = false;
  
  AssetModalFields asset_fields = AssetModalFields();

  AssetModel* current_asset = nullptr;
  Tool selected_tool;
  ImVec2 last_point;

  ////////////////////////////// FLAGS /////////////////////////////

  ImGuiColorEditFlags ColorPickerFlags() {
    ImGuiColorEditFlags color_picker_flags = ImGuiColorEditFlags_DisplayRGB;
    color_picker_flags |= ImGuiColorEditFlags_NoSidePreview;
    color_picker_flags |= ImGuiColorEditFlags_NoLabel;
    return color_picker_flags;
  }

  ImGuiWindowFlags DefaultWindowFlags() {
    ImGuiWindowFlags flags = ImGuiWindowFlags_AlwaysAutoResize;
    flags |= ImGuiWindowFlags_NoResize;
    return flags;
  }

  ////////////////////////////// DRAWING HANDLER ////////////////////////

  bool MouseInsideCanvas(ImVec2 mouse_pos, ImVec2 canvas_size) {
    return mouse_pos.x > 0 && mouse_pos.y > 0 && mouse_pos.x < canvas_size.x && mouse_pos.y < canvas_size.y;
  }

  void HandleMouseDown(ImVec2 mouse_pos) {
    this->last_point = mouse_pos;
  }

  void HandleMouseDragging(ImVec2 mouse_pos, ImVec2 canvas_pos, ImDrawList* draw_list) {
    // For Previews
    ImVec2 adjusted_start = AdjustToBase(canvas_pos, this->last_point);
    ImVec2 adjusted_end = AdjustToBase(canvas_pos, mouse_pos);
    
    if (selected_tool.type == ToolType::Pencil) {
      this->current_asset->objects_drawn.push_back(DrawnObject(this->selected_tool, this->last_point, mouse_pos));
      this->last_point = mouse_pos;
    } else if (selected_tool.type == ToolType::Line) {
      draw_list->AddLine(adjusted_start, adjusted_end, PreviewColor(selected_tool.color), selected_tool.size);
    } else if (selected_tool.type == ToolType::Rectangle) {
      draw_list->AddRect(adjusted_start, adjusted_end, PreviewColor(selected_tool.color), 0, 0, selected_tool.size);
    } else if (selected_tool.type == ToolType::Circle) {
      int radius = adjusted_end.x - adjusted_start.x;
      draw_list->AddCircle(adjusted_start, radius > 0 ? radius : -radius, PreviewColor(selected_tool.color), 0, selected_tool.size);
    }
  }

  void HandleMouseRelease(ImVec2 mouse_pos) {
    if (!selected_tool.type == ToolType::Pencil) {
      this->current_asset->objects_drawn.push_back(DrawnObject(this->selected_tool, this->last_point, mouse_pos));
    }
  }

  void DrawToCanvas(ImDrawList *draw_list, ImVec2 canvas_pos) {
    for(size_t i = 0; i < this->current_asset->objects_drawn.size(); i++) {
      DrawnObject object = this->current_asset->objects_drawn.at(i);
      ImVec2 adjusted_end_vec = ImVec2(canvas_pos.x + object.end.x, canvas_pos.y + object.end.y);
      ImVec2 adjusted_start_vec = ImVec2(canvas_pos.x + object.start.x, canvas_pos.y + object.start.y);
      
      if (object.drawn_by == ToolType::Pencil || object.drawn_by == ToolType::Line) {
        draw_list->AddLine(adjusted_start_vec, adjusted_end_vec, object.color, object.size);
      } else if (object.drawn_by == ToolType::Rectangle) {
        draw_list->AddRect(adjusted_start_vec, adjusted_end_vec, object.color, 0, 0, object.size);
      } else if (object.drawn_by == ToolType::Circle) {
        int radius = adjusted_end_vec.x - adjusted_start_vec.x;
        draw_list->AddCircle(adjusted_start_vec, radius > 0 ? radius : -radius, object.color, 0, object.size);
      }
    }
  }

  ////////////////////////////// ASSETS MANAGER /////////////////////////

  bool InvokeNewAsset() {
    string name_as_str = string(this->asset_fields.name);
    name_as_str = processName(name_as_str);
    if (name_as_str.size() == 0) return false;

    AssetModel* newAsset = new AssetModel(name_as_str, ImVec2(asset_fields.size_x, asset_fields.size_y));
    return ModelStorage::InsertAsset(newAsset);
  }

  bool IsAssetSelected(AssetModel* asset) {
    return asset->id == this->current_asset->id;
  }

  ////////////////////////////// COMPONENTS /////////////////////////////

  void ShowNewAssetModal() {
    ImGui::Begin("New Asset Form", &this->is_new_modal_open, DefaultWindowFlags());
      ImGui::InputText("Name", this->asset_fields.name, 64);
      ImGui::InputScalar("Width", ImGuiDataType_U16, &this->asset_fields.size_x);
      ImGui::InputScalar("Height", ImGuiDataType_U16, &this->asset_fields.size_y);

      if (ImGui::Button("Cancel")) this->is_new_modal_open = false;
      ImGui::SameLine();
      if (ImGui::Button("Accept")) {
        if (InvokeNewAsset()) {
          memset(this->asset_fields.name, '\0', 64);
          this->is_new_modal_open = false;
        }
      }
    ImGui::End();
  }

  void ShowDrawingArea() {
    ImGui::SetNextWindowSize(this->current_asset->canvas_size);
    ImGui::Begin("Asset Canvas", &this->is_open, ImGuiWindowFlags_NoResize);
      ImVec2 canvas_size = ImGui::GetContentRegionAvail();
      ImVec2 canvas_pos = ImGui::GetCursorScreenPos();  
      ImDrawList* draw_list = ImGui::GetWindowDrawList(); 

      ImGui::InvisibleButton("##Canvas", canvas_size);
      if (ImGui::IsItemHovered) {
        ImVec2 mouse_pos_in_canvas = ImVec2(ImGui::GetIO().MousePos.x - canvas_pos.x, ImGui::GetIO().MousePos.y - canvas_pos.y);
        if (MouseInsideCanvas(mouse_pos_in_canvas, canvas_size)) {
          if (ImGui::IsMouseDown(0) && !is_drawing) {
            this->is_drawing = true;
            this->HandleMouseDown(mouse_pos_in_canvas);
          }
          
          if (ImGui::IsMouseDown(0) && is_drawing) {
            this->HandleMouseDragging(mouse_pos_in_canvas, canvas_pos, draw_list);
          }
          
          if (ImGui::IsMouseReleased(0)) {
            this->is_drawing = false;
            this->HandleMouseRelease(mouse_pos_in_canvas);
          }        
        }
      }
      this->DrawToCanvas(draw_list, canvas_pos);
    ImGui::End();
  }

  void ShowControlButtons() {
    if (ImGui::Button("Save Asset")) {}
    ImGui::SameLine();
    if (ImGui::Button("New Asset")) this->is_new_modal_open = true;
  }

  void ShowAssetsList() {
    ImGui::Spacing();
    ImGui::Text("Assets List");

    ImVec2 avail_space = ImGui::GetContentRegionAvail();
    if (ImGui::BeginListBox("##avail_assets")) {
      for (size_t i = 0; i < ModelStorage::assets.size(); i++) {
        AssetModel* asset = ModelStorage::assets.at(i);
        if (ImGui::Selectable(asset->name.c_str())) {
          this->current_asset = asset;
        }
      }
      ImGui::EndListBox();
    }
  }

  void ShowDrawingControls() {
    ImGui::Begin("Canvas controls", &this->is_open, DefaultWindowFlags());
      ShowControlButtons();
      ImGui::ColorPicker4("##color_picker", this->selected_tool.color, ColorPickerFlags());
      ImGui::SliderInt("##Tool Size", &this->selected_tool.size, 1, 25);
      if (ImGui::BeginListBox("##Tool")) {
        if (ImGui::Selectable("Pencil", this->selected_tool.type == ToolType::Pencil)) {
          this->selected_tool.type = ToolType::Pencil;
        }
        if (ImGui::Selectable("Rectangle", this->selected_tool.type == ToolType::Rectangle)) {
          this->selected_tool.type = ToolType::Rectangle;
        }
        if (ImGui::Selectable("Line", this->selected_tool.type == ToolType::Line)) {
          this->selected_tool.type = ToolType::Line;
        }
        if (ImGui::Selectable("Circle", this->selected_tool.type == ToolType::Circle)) {
          this->selected_tool.type = ToolType::Circle;
        }
        ImGui::EndListBox();
      }
      ShowAssetsList();
    ImGui::End();
  }

public:
  void create() override {
    if (this->is_open) {
      ShowDrawingControls();
      if (this->current_asset != nullptr) ShowDrawingArea();
      if (this->is_new_modal_open) ShowNewAssetModal();
    }
  }
};