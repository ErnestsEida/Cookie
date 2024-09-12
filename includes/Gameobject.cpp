#pragma once
#include <iostream>
#include <vector>

#include "helpers/Generators.cpp"
#include "interfaces/IDrawable.cpp"

using namespace std;

const int defaultCoord = 0;
const string defaultTag = "";
const string defaultName = "object";

class GameObject {
private:
  vector<GameObject*> children = vector<GameObject*>();
  vector<IDrawable> drawables = vector<IDrawable>();

  Vector2f realCoords() {
    float tempX, tempY = 0;

    if (this->parent != nullptr) {
      tempX = this->parent->x;
      tempY = this->parent->y;
    }
    tempX += this->x;
    tempY += this->y;

    return Vector2f(tempX, tempY);
  }

  void processDrawables() {
    for(IDrawable drawable : drawables) {
      drawable.z = this->z;
      if (drawable.source != nullptr) {
        Transformable* transform = drawable.transformable();
        transform->setPosition(realCoords());
      }
    }
  }
public:
  GameObject* parent = nullptr;
  bool isVisible = true;
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

  virtual void addDrawable(Drawable* drawable) final {
    this->drawables.push_back(IDrawable(drawable, this->z));
  }

  virtual vector<IDrawable> gDrawables(vector<IDrawable> &result) final {    
    if (!this->drawables.empty() && this->isVisible) {
      this->processDrawables();
      result.insert(result.end(), this->drawables.begin(), this->drawables.end());
    }

    if (this->children.empty()) return result;

    for(GameObject* child : this->children) {
      vector<IDrawable> childDrawables = child->gDrawables(result);
      result.insert(result.end(), childDrawables.begin(), childDrawables.end());
    }

    return result;
  }

  virtual void beforeUpdate() {};
  virtual void onUpdate() {};
  virtual void afterUpdate() {};
};