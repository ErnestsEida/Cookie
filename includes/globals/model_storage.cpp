#pragma once
#include <vector>
#include <iostream>
#include "../data_structures/ScriptModel.cpp"
#include "../data_structures/AssetModel.cpp"
#include "../data_structures/GameObjectModel.cpp"

using namespace std;

class ModelStorage {
private:
  static bool GameObjectUnique(string id) {
    for (size_t i = 0; i < ModelStorage::gameobjects.size();i++) {
      if (ModelStorage::gameobjects.at(i)->id == id) return false;
    }
    return true;
  }

  static bool ScriptUnique(string id) {
    for (size_t i = 0; i < ModelStorage::scripts.size();i++) {
      if (ModelStorage::scripts.at(i)->id == id) return false;
    }
    return true;
  }

  static bool AssetUnique(string id) {
    for (size_t i = 0; i < ModelStorage::assets.size(); i++) {
      if (ModelStorage::assets.at(i)->id == id) return false;
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

  // Assets
  static vector<AssetModel*> assets;

  static bool DeleteAsset(string id) {
    for(size_t i = 0; i < ModelStorage::assets.size(); i++) {
      if (assets.at(i)->id == id) {
        assets.erase(assets.begin() + i);
        assets.shrink_to_fit();
        return true;
      }
    }
    return false;
  }

  static bool InsertAsset(AssetModel* asset) {
    if (asset == nullptr || !AssetUnique(asset->id)) return false;
    ModelStorage::assets.push_back(asset);
    return true;
  }

  // GameObjects
  static vector<GameObjectModel*> gameobjects;

  static bool DeleteGameObject(string id) {
    for(size_t i = 0; i < ModelStorage::gameobjects.size(); i++) {
      if (gameobjects.at(i)->id == id) {
        gameobjects.erase(gameobjects.begin() + i);
        gameobjects.shrink_to_fit();
        return true;
      }
    }
    return false;
  }

  static bool InsertGameObject(GameObjectModel* gameobject) {
    if (gameobject == nullptr || !GameObjectUnique(gameobject->id)) return false;
    ModelStorage::gameobjects.push_back(gameobject);
    return true;
  }

  static GameObjectModel* FindGameObject(string id) {
    for(size_t i = 0; i < gameobjects.size(); i++) {
      if (gameobjects.at(i)->id == id) return gameobjects.at(i);
    }
    return nullptr;
  }

  // GameRooms

};

vector<ScriptModel*> ModelStorage::scripts = vector<ScriptModel*>();
vector<AssetModel*> ModelStorage::assets = vector<AssetModel*>();
vector<GameObjectModel*> ModelStorage::gameobjects = vector<GameObjectModel*>();
