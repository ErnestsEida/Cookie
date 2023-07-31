#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <vector>
#include <chrono>
#include "interfaces/IDrawable.cpp"

using namespace sf;
using namespace std;
using namespace chrono;

const Vector3f DEFAULT_CORDS = Vector3f(0, 0, 0);
const string DEFAULT_OBJ_NAME = "object";
const string DEFAULT_TAG = "";

class GameObject {
protected:
  GameObject* parent = nullptr;

  void PushDrawable(Drawable* drawable) {
    this->drawables.push_back(IDrawable(drawable, this->z));
  }

public:
  vector<GameObject*> children;
  vector<IDrawable> drawables;
  float x, offset_x, y, offset_y;
  int z;
  string id, objectName, objectTag;
  bool isVisible = true;
  bool isChild = false;

  GameObject(string id = "none", int x = DEFAULT_CORDS.x, int y = DEFAULT_CORDS.y, int z = DEFAULT_CORDS.z, string objectName = DEFAULT_OBJ_NAME, string objectTag = DEFAULT_TAG) {
    if (id == "none") {
      uint64_t millisec = system_clock::now().time_since_epoch().count();
      this->id = to_string(millisec);
    } else {
      this->id = id;
    }
    this->x = this->offset_x = x;
    this->y = this->offset_y = y;
    this->z = z;
    this->objectName = objectName;
    this->objectTag = objectTag;
  }

  // Miscelaneous

  vector<IDrawable> getDrawables() {
    vector<IDrawable> resulting_drawables;
    if (this->children.size() != 0) {
        for(size_t i = 0; i < this->children.size(); i++) {
            GameObject* child = this->children.at(i);
            vector<IDrawable> children_drawables = child->getDrawables();
            resulting_drawables.insert(resulting_drawables.end(), children_drawables.begin(), children_drawables.end());
        }
    }

    resulting_drawables.insert(resulting_drawables.end(), this->drawables.begin(), this->drawables.end());

    return resulting_drawables;
  }

  void UpdateDrawables() {
    if (this->children.size() != 0) {
      for(size_t i = 0; i < this->children.size(); i++) {
          this->children.at(i)->UpdateDrawables();
      }
    }
    
    Transformable* asTransformable;
    for(size_t i = 0; i < this->drawables.size(); i++) {
      this->drawables.at(i).z = this->z;
      asTransformable = dynamic_cast<Transformable*>(this->drawables.at(i).drawable);
      asTransformable->setPosition(this->x, this->y);
    }
  }

  void UpdateChildren() {
    if (this->children.size() == 0) return;
    for(size_t i = 0; i < this->children.size(); i++) {
        GameObject* child = this->children.at(i);
        child->Update();
        child->x = this->x + child->offset_x;
        child->y = this->y + child->offset_y;
        child->UpdateChildren();
    }
  }

  void PushChild(GameObject* object) {
    object->isChild = true;
    object->parent = this;
    object->x = this->x + object->offset_x;
    object->y = this->y + object->offset_y;
    this->children.push_back(object);
  }

  // Virtual Methods

  virtual void Update() = 0;

  // STATIC METHODS
  // 
  //
};