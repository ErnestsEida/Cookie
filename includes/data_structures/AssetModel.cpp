#pragma once
#include <iostream>
#include <vector>
#include "../imgui/imgui.h"
#include "../helpers/generator.cpp"
#include "../helpers/AssetManagerIndex.cpp"

using namespace std;

class AssetModel {
public:
  string id, name;
  ImVec2 canvas_size;
  vector<DrawnObject> objects_drawn;

  AssetModel(string name, ImVec2 canvas_size, vector<DrawnObject> objects_drawn = vector<DrawnObject>()) {
    this->id = Generator::GenerateID();
    this->name = name;
    this->canvas_size = canvas_size;
    this->objects_drawn = objects_drawn;
  }
};