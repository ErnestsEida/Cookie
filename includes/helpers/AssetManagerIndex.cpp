#pragma once
#include "../imgui/imgui.h"
#include "../externals/stb_image.h"

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
  float color[4] = {0, 0, 0, 1};
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

string GetImagenameFrompPath(string path) {
  char seperator = '/';
  vector<string> words;
  string temp_word = "";
  for(int i = 0;i < path.length(); i++) {
    if (path[i] == seperator) {
      words.push_back(temp_word);
      temp_word = "";
    } else {
      temp_word += path[i];
    }
  }
  words.push_back(temp_word);
  return words.at(words.size() - 1);
}

// TODO: Create a function that takes in the path of the file and converts it into AssetModel, which values
// can be copied to the actual Asset that would be later inserted into the model_storage;
// Most probably will need to draw pixel by pixel to the ImDrawList with lines as was said in some post
vector<DrawnObject*> CreateAssetFromImage(string path_to_image) {
  int image_width, image_height, image_channels;
  uint8_t* rgb_image = stbi_load(path_to_image.c_str(), &image_width, &image_height, &image_channels, 3);
  return 
}