#pragma once
#include <vector>

#include "GameObject.cpp"
#include "Alerts.cpp"

using namespace std;

class Scene {
private:
    vector<GameObject*> objects_in_scene = vector<GameObject*>();
public:
    Scene() {}

    void AddGameObject(GameObject* object) {
        this->objects_in_scene.push_back(object);
    }

    void RemoveGameObject(GameObject* object) {}

    vector<GameObject*> GetGameObjects() {
        vector<GameObject*> parent_objects;
        for(size_t i = 0; i < objects_in_scene.size(); i++) {
            if (objects_in_scene.at(i)->isParent()){
                parent_objects.push_back(objects_in_scene.at(i));
            }
        }
        return parent_objects;
    }

    void ClearGameObjects() {
        // for(size_t i = 0; i < objects_in_scene.size(); i++) {
        //     delete objects_in_scene.at(i);
        // }
        // GameObject::object_count = 0;
        this->objects_in_scene.clear();
    }

    virtual void SetupScene() = 0;
};