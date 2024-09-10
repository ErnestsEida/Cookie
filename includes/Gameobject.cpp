#pragma once
#include <iostream>

#include "helpers/Generators.cpp"

using namespace std;

const int defaultCoord = 0;
const string defaultTag = "";
const string defaultName = "object";

class GameObject {
private:
  vector<GameObject*> children = vector<GameObject*>();
public:
  GameObject* parent = nullptr;
  string objectName;
  string tag;
  string id;
  float x;
  float y;
  int z;

  GameObject(int x = defaultCoord, int y = defaultCoord, int z = defaultCoord, string objectName = defaultName, string tag = defaultTag) {
    this->id = Generators::MakeUniqID("gameobject_");
    this->objectName = objectName;
    this->tag = tag;
    this->x = x;
    this->y = y;
    this->z = z;
  }

  virtual void addChild(GameObject* child) final {
    child->parent = this;
    this->children.push_back(child);
  }

  virtual void processChildren(string regulator) final {
    if (children.empty()) return;
  
    for(GameObject* child : children) {
      if (regulator == "before") {
        child->beforeUpdate();
      } else if (regulator == "on") {
        child->onUpdate();
      } else if (regulator == "after") {
        child->afterUpdate();
      }
      child->processChildren(regulator);
    }
  }

  virtual void processColliders() final {
    /* TODO */
  }

  virtual void drawables() final {
    /* TODO */
  }

  virtual void beforeUpdate() = 0;
  virtual void onUpdate() = 0;
  virtual void afterUpdate() = 0;
};