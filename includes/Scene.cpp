#pragma once
#include "Gameobject.cpp"
#include "Profiler.cpp"
#include <vector>

using namespace std;

class Scene {
public:
  static vector<pair<string, Scene*>> scenes;
  
  static void AddScene(string title, Scene* scene) {
    if (scene == nullptr) Profiler::Warning("[ADDING ROOM] Room '" + title + "' is a null pointer");

    scenes.push_back(make_pair(title, scene));
  }

  static Scene* GetScene(string title) {
    Scene* scene = nullptr;

    for(ulong i = 0; i < scenes.size(); i++) {
      if (scenes.at(i).first == title) {
        scene = scenes.at(i).second;
        break;
      }
    }
    
    return scene;
  }

  virtual vector<GameObject*> GenerateObjects() = 0;
};

vector<pair<string, Scene*>> Scene::scenes = vector<pair<string, Scene*>>();