#pragma once
#include <iostream>
#include <vector>
#include "../helpers/generator.cpp"
#include "../imgui/imgui.h"

using namespace std;

enum GameObjectChildType {
  Node,
  Collider,
  SpriteRenderer,
};

enum PresetShapeType {
  _Circle,
  _Rectancle,
};

enum RendererType {
  Animation,
  Preset,
};

// GOC - GameObjectChild
struct GOC_ColliderData {
  float size[2] = { 0, 0 };
  float offset[2] = { 0, 0 };

  GOC_ColliderData() {}
  GOC_ColliderData(ImVec2 c_size, ImVec2 c_offset) {
    size[0] = c_size.x;
    size[1] = c_size.y;
    offset[0] = c_offset.x;
    offset[1] = c_offset.y;
  }
};

struct GOC_RendererData {
  RendererType type = RendererType::Preset;
  PresetShapeType shape = PresetShapeType::_Rectancle; // IF RendererType::Preset
  float shape_size[2] = { 0, 0 }; // IF RendererType::Preset
  string animation_id = ""; // IF RendererType::Animation

  GOC_RendererData() {}
};

struct GOC_NodeData {
  string node_id = "";
  float offset[3] = { 0, 0, 0 };

  GOC_NodeData() {}
  GOC_NodeData(string id, float child_offset[3]) {
    node_id = id;
    // Real funny loop, but it felt sad to write out all 3 values manually :) - i know it goes agains what i said elsewhere
    for(int i = 0; i < 3; i++) {
      offset[i] = child_offset[i];
    }
  }
};
// ====================

class GameObjectChild {
public:
  string id;
  GameObjectChildType type;
  GOC_ColliderData collider_data;
  GOC_RendererData renderer_data;
  GOC_NodeData node_data;

  GameObjectChild() {}

  GameObjectChild(GOC_ColliderData data) {
    this->id = Generator::GenerateID();
    this->type = GameObjectChildType::Collider;
    this->collider_data = data;
  }

  GameObjectChild(GOC_NodeData data) {
    this->id = Generator::GenerateID();
    this->type = GameObjectChildType::Node;
    this->node_data = data;
  }

  GameObjectChild(GOC_RendererData data) {
    this->id = Generator::GenerateID();
    this->type = GameObjectChildType::SpriteRenderer;
    this->renderer_data = data;
  }

};

class GameObjectModel
{
public:
  string id, name, tag;
  float x = 0;
  float y = 0;
  int z = 0;

  vector<GameObjectChild*> children;
  vector<string> script_ids;
  vector<string> asset_ids;

  GameObjectModel(string name, float x, float y, int z)
  {
    this->id = Generator::GenerateID();
    this->name = name;
    this->x = x;
    this->y = y;
    this->z = z;
  }
};