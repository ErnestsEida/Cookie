#pragma once
#include "../imgui/imgui.h"

ImU32 TranslateColor(float color[4]) {
  ImVec4 color_as_vec = ImVec4(color[0], color[1], color[2], color[3]);
  return ImGui::ColorConvertFloat4ToU32(color_as_vec);
}

ImU32 PreviewColor(float color[4]) {
  ImVec4 color_as_vec = ImVec4(color[0], color[1], color[2], 0.5f);
  return ImGui::ColorConvertFloat4ToU32(color_as_vec);
}

ImVec2 AdjustToBase(ImVec2 base, ImVec2 adjustable) {
  return ImVec2(base.x + adjustable.x, base.y + adjustable.y);
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