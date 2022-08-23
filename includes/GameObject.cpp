#include "GameObject.hpp"

const int DEFAULT_Z = 0;
const string DEFAULT_OBJECT_NAME = "object";
const string DEFAULT_TAG = "none";

int GameObject::objectCount = 0;
vector<GameObject*> GameObject::objects;

GameObject::GameObject(int x, int y) {
    this->x = x;
    this->y = y;
    this->z = DEFAULT_Z;
    this->objectName = DEFAULT_OBJECT_NAME + to_string(GameObject::objectCount);
    this->tag = DEFAULT_TAG;
    GameObject::objectCount++;
    GameObject::objects.push_back(this);
}

GameObject::GameObject(int x, int y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
    this->objectName = DEFAULT_OBJECT_NAME + to_string(GameObject::objectCount);
    this->tag = DEFAULT_TAG;
    GameObject::objectCount++;
    GameObject::objects.push_back(this);
}

GameObject::GameObject(int x, int y, float z, string objectName) {
    this->x = x;
    this->y = y;
    this->z = DEFAULT_Z;
    this->objectName = objectName;
    this->tag = DEFAULT_TAG;
    GameObject::objectCount++;
    GameObject::objects.push_back(this);
}

GameObject::GameObject(int x, int y, float z, string objectName, string tag) {
    this->x = x;
    this->y = y;
    this->z = DEFAULT_Z;
    this->objectName = objectName;
    this->tag = tag;
    GameObject::objectCount++;
    GameObject::objects.push_back(this);
}

void GameObject::SortObjectsByZ() {
    // SORT ALL GAMEOBJECTS BY THEIR Z INDEX
}