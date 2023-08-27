#pragma once
#include <iostream>
#include <vector>
#include "../helpers/generator.cpp"

using namespace std;

class GameObjectModel
{
public:
  string id, name, tag;
  float x = 0;
  float y = 0;
  int z = 0;

  vector<GameObjectModel*> children;
  vector<string> script_ids;
  vector<string> asset_ids;

  GameObjectModel(string name)
  {
    this->id = Generator::GenerateID();
    this->name = name;
  }
};