#pragma once
#include "interfaces/IDisplayWindow.cpp"
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

ImU32 TranslateColor(float color[4]) {
  ImVec4 color_as_vec = ImVec4(color[0], color[1], color[2], color[3]);
  return ImGui::ColorConvertFloat4ToU32(color_as_vec);
}

enum ToolType {
  Pencil,
  Circle,
  Rectangle,
  Line,
};

struct Tool {
  ToolType type = ToolType::Pencil;
  int size = 1;
  float color[4] = {1, 1, 1, 1};
};

struct DrawnObject {
  ToolType drawn_by;
  int size;
  ImU32 color;
  ImVec2 start;
  ImVec2 end;

  DrawnObject() {}

  DrawnObject(Tool drawn_by_tool, ImVec2 start, ImVec2 end = ImVec2(0, 0)) {
    this->drawn_by = drawn_by_tool.type;
    this->color = TranslateColor(drawn_by_tool.color);
    this->size = drawn_by_tool.size;
    this->start = start;
    this->end = end;
  }
};

class AssetsManager : public IDisplayWindow {
private:
  bool draw_area_set = false;
  bool is_drawing = false;
  
  Tool selected_tool;
  vector<DrawnObject> drawn_objects = vector<DrawnObject>();
  ImVec2 last_point;

  ////////////////////////////// FLAGS /////////////////////////////

  ImGuiColorEditFlags ColorPickerFlags() {
    ImGuiColorEditFlags color_picker_flags = ImGuiColorEditFlags_DisplayRGB;
    color_picker_flags |= ImGuiColorEditFlags_NoSidePreview;
    return color_picker_flags;
  }

  ////////////////////////////// DRAWING HANDLER ////////////////////////

  bool MouseInsideCanvas(ImVec2 mouse_pos, ImVec2 canvas_size) {
    return mouse_pos.x > 0 && mouse_pos.y > 0 && mouse_pos.x < canvas_size.x && mouse_pos.y < canvas_size.y;
  }

  void HandleMouseDown(ImVec2 mouse_pos) {
    this->last_point = mouse_pos;
  }

  void HandleMouseDragging(ImVec2 mouse_pos) {
    if (selected_tool.type == ToolType::Pencil) {
      this->drawn_objects.push_back(DrawnObject(this->selected_tool, this->last_point, mouse_pos));
      this->last_point = mouse_pos;
    } else if (selected_tool.type == ToolType::Line) {
      // Preview
    } else if (selected_tool.type == ToolType::Rectangle) {
      // Preview
    } else if (selected_tool.type == ToolType::Circle) {
      // Preview
    }
  }

  void HandleMouseRelease(ImVec2 mouse_pos) {
    if (!selected_tool.type == ToolType::Pencil) {
      this->drawn_objects.push_back(DrawnObject(this->selected_tool, this->last_point, mouse_pos));
    }
  }

  void DrawToCanvas(ImDrawList *draw_list, ImVec2 canvas_pos) {
    for(size_t i = 0; i < this->drawn_objects.size(); i++) {
      DrawnObject object = this->drawn_objects.at(i);
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

  ////////////////////////////// COMPONENTS /////////////////////////////

  void ShowDrawingArea() {
    if (!this->draw_area_set) {
      ImGui::SetNextWindowSize(ImVec2(720, 480));
      this->draw_area_set = true;
    }

    ImGui::Begin("Asset Canvas", &this->is_open);
      ImVec2 canvas_size = ImGui::GetContentRegionAvail();
      ImVec2 canvas_pos = ImGui::GetCursorScreenPos();  

      ImGui::InvisibleButton("##Canvas", canvas_size);
      if (ImGui::IsItemHovered) {
        ImVec2 mouse_pos_in_canvas = ImVec2(ImGui::GetIO().MousePos.x - canvas_pos.x, ImGui::GetIO().MousePos.y - canvas_pos.y);
        if (MouseInsideCanvas(mouse_pos_in_canvas, canvas_size)) {
          if (ImGui::IsMouseDown(0) && !is_drawing) {
            this->is_drawing = true;
            this->HandleMouseDown(mouse_pos_in_canvas);
          }
          
          if (ImGui::IsMouseDown(0) && is_drawing) {
            this->HandleMouseDragging(mouse_pos_in_canvas);
          }
          
          if (ImGui::IsMouseReleased(0)) {
            this->is_drawing = false;
            this->HandleMouseRelease(mouse_pos_in_canvas);
          }        
        }
      }
      ImDrawList* draw_list = ImGui::GetWindowDrawList();
      this->DrawToCanvas(draw_list, canvas_pos);
    ImGui::End();
  }

  void ShowControlButtons() {
    if (ImGui::Button("Save Asset")) {
      // Save asset
    }

    ImGui::SameLine();
    if (ImGui::Button("New Asset")) {
      // New Asset
    }
  }

  void ShowDrawingControls() {
    ImGui::SetNextWindowSize(ImVec2(250, 400));

    ImGui::Begin("Canvas controls", &this->is_open);
      ShowControlButtons();
      
      ImGui::ColorPicker4("##color_picker", this->selected_tool.color, ColorPickerFlags());
      ImGui::SliderInt("Tool Size", &this->selected_tool.size, 1, 25);
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