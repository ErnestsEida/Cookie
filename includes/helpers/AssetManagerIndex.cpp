#pragma once
#include "../imgui/imgui.h"
#include "../libs/stb_image.h"
#include <iostream>
#include <vector>

using namespace std;

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
  ImageRenderer,
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

struct ImageAssetData {
  vector<DrawnObject> drawn_objects;
  int width, height;
  string name;
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

ImageAssetData CreateAssetFromImage(string path_to_image) {
  Tool image_tool;
  image_tool.size = 2;
  image_tool.type = ToolType::Line;
  
  vector<DrawnObject> drawn_objects;
  int width, height, channels;
  stbi_uc* image = stbi_load(path_to_image.c_str(), &width, &height, &channels, 4);
  
  for (int y = 0; y < height; ++y) {
    for (int x = 0; x < width - 1; ++x) {
        // GET CURRENT PIXEL DATA
        float rgba[4];
        int pixel_index = (y * width + x) * 4;
        rgba[0] = float(image[pixel_index]) / 255;
        rgba[1] = float(image[pixel_index + 1]) / 255;
        rgba[2] = float(image[pixel_index + 2]) / 255;
        rgba[3] = float(image[pixel_index + 3]) / 255;
        // Create color
        DrawnObject new_object(image_tool, ImVec2(x, y), ImVec2(x+1, y));
        new_object.color = TranslateColor(rgba);
        drawn_objects.push_back(new_object);
    }
  }

  ImageAssetData data;
  data.drawn_objects = drawn_objects;
  data.width = width;
  data.height = height;
  data.name = GetImagenameFrompPath(path_to_image);

  return data;
}