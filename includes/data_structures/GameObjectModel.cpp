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

class GameObjectChild {
public:
  GameObjectChildType type;
  string child_id = ""; // Used for 'node' type children, to store another gameobjects id, so it can be linked together
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