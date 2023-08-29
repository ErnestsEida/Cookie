#pragma once
#include <iostream>
#include <vector>
#include "../helpers/generator.cpp"

using namespace std;

enum GameObjectChildType {
  Node,
  Collider,
  SpriteRenderer,
};

enum PresetShapeType {
  Circle,
  Rectangle,
};

enum RendererType {
  Animation,
  Preset,
};

// GOC - GameObjectChild
struct GOC_ColliderData {
  float size[2] = { 0, 0 };
  float offset[2] = { 0, 0 };
};

struct GOC_RendererData {
  RendererType type = RendererType::Preset;
  PresetShapeType shape = PresetShapeType::Rectangle;
  float shape_size[2] = { 0, 0 }; // IF RendererType::Preset
  string animation_id = ""; // IF RendererType::Animation
};

struct GOC_NodeData {
  string node_id = "";
};
// ====================

class GameObjectChild {
public:
  GameObjectChildType type;
  GOC_ColliderData collider_data;
  GOC_RendererData renderer_data;
  GOC_NodeData node_data;
};

class GameObjectModel
{
public:
  string id, name, tag;
  float x = 0;
  float y = 0;
  int z = 0;

  vector<GameObjectChild> children;
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