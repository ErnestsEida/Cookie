#pragma once
#include "externals/imfilebrowser.h"
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
  ImGui::FileBrowser fileDialog;

  AssetModel* current_asset = nullptr;
  Tool selected_tool;
  ImVec2 last_point;
  float zoom_amount = 1.0f;

  ImVec2 AdjustMouseForZoom(ImVec2 mouse_pos) {
    return ImVec2(mouse_pos.x / this->zoom_amount, mouse_pos.y / this->zoom_amount);
  }

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
    flags |= ImGuiWindowFlags_NoScrollbar;
    return flags;
  }

  ////////////////////////////// DRAWING HANDLER ////////////////////////

  bool MouseInsideCanvas(ImVec2 mouse_pos, ImVec2 canvas_size) {
    return mouse_pos.x > 0 && mouse_pos.y > 0 && mouse_pos.x < canvas_size.x && mouse_pos.y < canvas_size.y;
  }

  void HandleMouseDown(ImVec2 mouse_pos) {
    this->last_point = AdjustMouseForZoom(mouse_pos);
  }

  void HandleMouseDragging(ImVec2 mouse_pos, ImVec2 canvas_pos, ImDrawList* draw_list) {
    // For Previews
    ImVec2 adjusted_start = AdjustToBase(canvas_pos, ImVec2(this->last_point.x * this->zoom_amount, this->last_point.y * this->zoom_amount));
    ImVec2 adjusted_end = AdjustToBase(canvas_pos, mouse_pos);
    float real_size = this->selected_tool.size * this->zoom_amount;
    
    if (selected_tool.type == ToolType::Pencil) {
      this->current_asset->objects_drawn.push_back(DrawnObject(this->selected_tool, this->last_point, AdjustMouseForZoom(mouse_pos)));
      this->last_point = AdjustMouseForZoom(mouse_pos);
    } else if (selected_tool.type == ToolType::Line) {
      draw_list->AddLine(adjusted_start, adjusted_end, PreviewColor(selected_tool.color), real_size);
    } else if (selected_tool.type == ToolType::Rectangle) {
      draw_list->AddRect(adjusted_start, adjusted_end, PreviewColor(selected_tool.color), 0, 0, real_size);
    } else if (selected_tool.type == ToolType::Circle) {
      int radius = adjusted_end.x - adjusted_start.x;
      draw_list->AddCircle(adjusted_start, radius > 0 ? radius : -radius, PreviewColor(selected_tool.color), 0, real_size);
    }
  }

  void HandleMouseRelease(ImVec2 mouse_pos) {
    if (!selected_tool.type == ToolType::Pencil) {
      this->current_asset->objects_drawn.push_back(DrawnObject(this->selected_tool, this->last_point, AdjustMouseForZoom(mouse_pos)));
    }
  }

  void DrawToCanvas(ImDrawList *draw_list, ImVec2 canvas_pos, ImVec2 canvas_size) {
    for(size_t i = 0; i < this->current_asset->objects_drawn.size(); i++) {
      DrawnObject object = this->current_asset->objects_drawn.at(i);
      // float zoom_factor = (canvas_size.x / this->current_asset->canvas_size.x);
      float zoom_factor = this->zoom_amount;
      
      float adjusted_start_x = object.start.x * zoom_factor;
      float adjusted_start_y = object.start.y * zoom_factor;
      ImVec2 adjusted_start_vec = ImVec2(canvas_pos.x + adjusted_start_x, canvas_pos.y + adjusted_start_y);

      float adjusted_end_x = object.end.x * zoom_factor;
      float adjustd_end_y = object.end.y * zoom_factor;
      ImVec2 adjusted_end_vec = ImVec2(canvas_pos.x + adjusted_end_x, canvas_pos.y + adjustd_end_y);
      
      float real_size = object.size * this->zoom_amount;

      if (object.drawn_by == ToolType::Pencil || object.drawn_by == ToolType::Line) {
        draw_list->AddLine(adjusted_start_vec, adjusted_end_vec, object.color, real_size);
      } else if (object.drawn_by == ToolType::Rectangle) {
        draw_list->AddRect(adjusted_start_vec, adjusted_end_vec, object.color, 0, 0, real_size);
      } else if (object.drawn_by == ToolType::Circle) {
        int radius = adjusted_end_vec.x - adjusted_start_vec.x;
        draw_list->AddCircle(adjusted_start_vec, radius > 0 ? radius : -radius, object.color, 0, real_size);
      }
    }
  }

  ////////////////////////////// ASSETS MANAGER /////////////////////////

  bool InvokeNewAsset() {
    string name_as_str = string(this->asset_fields.name);
    name_as_str = processName(name_as_str);
    if (name_as_str.size() == 0) return false;
    if (this->asset_fields.size_x <= 0 || this->asset_fields.size_y <= 0) return false;

    // Adjust for padding or something
    this->asset_fields.size_x += 16;
    this->asset_fields.size_y += 16;

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
          this->asset_fields.size_x = 0;
          this->asset_fields.size_y = 0;
          this->is_new_modal_open = false;
        }
      }
    ImGui::End();
  }

  void ShowDrawingArea() {
    ImGui::Begin("Asset Canvas", &this->is_open);
      ImDrawList* draw_list = ImGui::GetWindowDrawList();
      if (this->current_asset != nullptr) {
        ImVec2 adjusted_canvas_size_with_zoom = ImVec2(this->current_asset->canvas_size.x * zoom_amount, this->current_asset->canvas_size.y * zoom_amount);
        if (ImGui::BeginChild("##Drawing_space", adjusted_canvas_size_with_zoom, true, ImGuiWindowFlags_NoScrollbar)) {
          ImVec2 canvas_size = ImGui::GetContentRegionAvail();
          ImVec2 canvas_pos = ImGui::GetCursorScreenPos();  
          draw_list->AddRectFilled(canvas_pos,ImVec2(canvas_pos.x + canvas_size.x, canvas_pos.y + canvas_size.y), IM_COL32_WHITE);

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
            } else if (this->is_drawing) {
              this->is_drawing = false;
            }
          }
          this->DrawToCanvas(draw_list, canvas_pos, canvas_size);
          
          ImGui::EndChild();
        }
      }
    ImGui::End();
  }

  void ShowControlButtons() {
    if (ImGui::Button("Save Asset")) {}
    ImGui::SameLine();
    if (ImGui::Button("New Asset")) this->is_new_modal_open = true;
    ImGui::SameLine();
    if (ImGui::Button("Import")) this->fileDialog.Open();
    this->fileDialog.Display();

    if (this->fileDialog.HasSelected()) {
      cout << this->fileDialog.GetSelected().string() << endl;
      this->fileDialog.ClearSelected();
    }
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
      ImGui::SliderFloat("Zoom", &this->zoom_amount, 1, 8);
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
  AssetsManager() {
    this->fileDialog = ImGui::FileBrowser();
    this->fileDialog.SetTitle("Select an image/spritesheet");
  }

  void create() override {
    if (this->is_open) {
      ShowDrawingControls();
      ShowDrawingArea();
      if (this->is_new_modal_open) ShowNewAssetModal();
    }
  }
};