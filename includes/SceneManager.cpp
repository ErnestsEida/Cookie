#pragma once
#include <iostream>
#include <map>

#include "Scene.cpp"

class SceneManager {
private:
    static map<string, Scene*> game_scenes;
public:
    static void AddScene(string scene_name, Scene* scene_object) {
        SceneManager::game_scenes.insert(pair<string, Scene*>(scene_name, scene_object));
    }

    static Scene* GetScene(string scene_name) {
        return SceneManager::game_scenes.at(scene_name);
    }
};

map<string, Scene*> SceneManager::game_scenes = map<string, Scene*>();