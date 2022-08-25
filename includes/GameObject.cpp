#include "GameObject.hpp"

const int DEFAULT_Z = 0;
const string DEFAULT_OBJECT_NAME = "object";
const string DEFAULT_TAG = "none";

int GameObject::objectCount = 0;
vector<GameObject*> GameObject::objects;

GameObject::GameObject(float x, float y) {
    this->x = x;
    this->mirrorX = x;
    this->y = y;
    this->mirrorY = y;
    this->z = DEFAULT_Z;
    this->objectName = DEFAULT_OBJECT_NAME + to_string(GameObject::objectCount);
    this->tag = DEFAULT_TAG;
    this->setCollider(1, 1);
    GameObject::objectCount++;
    GameObject::objects.push_back(this);
}

GameObject::GameObject(float x, float y, float z) {
    this->x = x;
    this->mirrorX = x;
    this->y = y;
    this->mirrorY = y;
    this->z = z;
    this->objectName = DEFAULT_OBJECT_NAME + to_string(GameObject::objectCount);
    this->tag = DEFAULT_TAG;
    this->setCollider(1, 1);
    GameObject::objectCount++;
    GameObject::objects.push_back(this);
}

GameObject::GameObject(float x, float y, float z, string objectName) {
    this->x = x;
    this->mirrorX = x;
    this->y = y;
    this->mirrorY = y;
    this->z = DEFAULT_Z;
    this->objectName = objectName;
    this->tag = DEFAULT_TAG;
    this->setCollider(1, 1);
    GameObject::objectCount++;
    GameObject::objects.push_back(this);
}

GameObject::GameObject(float x, float y, float z, string objectName, string tag) {
    this->x = x;
    this->mirrorX = x;
    this->y = y;
    this->mirrorY = y;
    this->z = DEFAULT_Z;
    this->objectName = objectName;
    this->tag = tag;
    this->setCollider(1, 1);
    GameObject::objectCount++;
    GameObject::objects.push_back(this);
}

void GameObject::SortObjectsByZ() {
    int iterations = 1;
    while(iterations > 0){
        iterations = 0;
        for(int i = 0; i < GameObject::objects.size(); i++){
            if (i == GameObject::objects.size() - 1) continue;

            if (GameObject::objects.at(i)->getZ() > GameObject::objects.at(i+1)->getZ()){
                iter_swap(GameObject::objects.begin() + i, GameObject::objects.begin() + (i+1));
                iterations++;
            }
        }
    }
}

vector<GameObject*> GameObject::getAllObjects() {
    return GameObject::objects;
}

vector<GameObject*> GameObject::getParentObjects() {
    vector<GameObject*> result;
    for(int i = 0; i < GameObject::objects.size(); i++){
        if (!GameObject::objects[i]->isChild) result.push_back(GameObject::objects[i]);
    }
    return result;
}

vector<GameObject*> GameObject::getChildObjects() {
    vector<GameObject*> result;
    for(int i = 0; i < GameObject::objects.size(); i++){
        if (GameObject::objects[i]->isChild) result.push_back(GameObject::objects[i]);
    }
    return result;
}