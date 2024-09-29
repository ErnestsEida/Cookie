#pragma once

#include "../Scene.cpp"
#include "../Gameobject.cpp"

class SceneManager {
private:
  void Init() {
    if (Scene::scenes.empty()) Profiler::Error("FATAL(SceneManager): At least 1 scene has to be added - add it via Scene::AddScene(...)");
    this->performChange(Scene::scenes.at(0).second);
  }

  void performChange(Scene* nextScene) {
    if (!nextScene->persistant || nextScene->objects.empty()) {
      nextScene->reset();
    }

    this->currentScene = nextScene;
  }
public:
  Scene* currentScene;

  SceneManager() {
    Init();
  }

  void resetCurrentScene() {
    this->currentScene->reset();
  }

  void changeScene(string sceneName) {
    Scene* nextScene = Scene::GetScene(sceneName);

    if (nextScene == nullptr) {
      Profiler::Warning("[SCENE CHANGE] Scene named '" + sceneName + "' does not exist in scene registry - add it via Scene::AddScene(...)");
    } else {
      this->performChange(nextScene);
    }
  }

  void insertObject(GameObject* newObject) {
    if (newObject == nullptr) Profiler::Warning("[SCENE MANAGER] Trying to insert new gameobject into scene with pointer to nullptr");
    this->currentScene->objects.push_back(newObject);
  }
};