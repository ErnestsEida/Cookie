#pragma once
#include <vector>
#include <iostream>
#include "../data_structures/ScriptModel.cpp"


using namespace std;

class ModelStorage {
private:
  static bool ScriptUnique(string id) {
    for (size_t i = 0; i < ModelStorage::scripts.size();i++) {
      if (ModelStorage::scripts.at(i)->id == id) return false;
    }
    return true;
  }
public:
  // Scripts
  static vector<ScriptModel*> scripts;

  static bool DeleteScript(string id) {
    for(size_t i = 0; i < ModelStorage::scripts.size(); i++) {
      if (scripts.at(i)->id == id) {
        scripts.erase(scripts.begin() + i);
        scripts.shrink_to_fit();
        return true;
      }
    }
    return false;
  }

  static bool InsertScript(ScriptModel* script) {
    if (script == nullptr || !ScriptUnique(script->id)) return false;  
    ModelStorage::scripts.push_back(script);
    return true;
  }

  // GameObjects

  // GameRooms

  // Assets

};

vector<ScriptModel*> ModelStorage::scripts = vector<ScriptModel*>();