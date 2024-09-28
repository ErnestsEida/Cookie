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

  void processDrawables() {
    for(IDrawable drawable : drawables) {
      drawable.z = this->z;
      if (drawable.source != nullptr) {
        Transformable* transform = drawable.transformable();
        transform->setPosition(this->realCoords());
      }
    }
  }
protected:
  Vector2f realCoords() {
    Vector2f parentPos = Vector2f(0, 0);
    Vector2f myPos = Vector2f(this->x, this->y);
    
    if (this->parent != nullptr) {
      parentPos = this->parent->realCoords();
    }

    return Vector2f(myPos.x + parentPos.x, myPos.y + parentPos.y);
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