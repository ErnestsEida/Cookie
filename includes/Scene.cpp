#pragma once
#include "Gameobject.cpp"
#include "Profiler.cpp"
#include <vector>

using namespace std;

class Scene {
public:
  static vector<pair<string, Scene*>> scenes;
  bool persistant = false;
  vector<GameObject*> objects = vector<GameObject*>();

  static void AddScene(string title, Scene* scene) {
    bool valid = true;

    if (scene == nullptr) {
      Profiler::Warning("[SCENE ADD] Scene '" + title + "' is a null pointer");
      valid = false;
    } else if (GetScene(title) != nullptr) {
      Profiler::Warning("[SCENE ADD] Key '" + title + "' is already set");
      valid = false;
    }

    if (valid) scenes.push_back(make_pair(title, scene));
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

  Scene(bool persistant = false) {
    this->persistant = persistant;
  }

  virtual void reset() final {
    this->objects = GenerateObjects();
  }

  virtual vector<GameObject*> GenerateObjects() = 0;
};

vector<pair<string, Scene*>> Scene::scenes = vector<pair<string, Scene*>>();