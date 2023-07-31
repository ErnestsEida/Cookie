#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <vector>
#include "interfaces/IDrawable.cpp"

using namespace sf;
using namespace std;

const Vector3f DEFAULT_CORDS = Vector3f(0, 0, 0);
const string DEFAULT_OBJ_NAME = "object";
const string DEFAULT_TAG = "";

class GameObject {
private:
  bool isChild = false;
  vector<GameObject*> children;
  vector<IDrawable> drawables;

protected:
  GameObject* parent = nullptr;

  void PushDrawable(Drawable* drawable) {
    this->drawables.push_back(IDrawable(drawable, this->z));
  }

public:
  float x, offset_x, y, offset_y;
  int z;
  string id, objectName, objectTag;
  bool isVisible = true;

  GameObject(string id, int x = DEFAULT_CORDS.x, int y = DEFAULT_CORDS.y, int z = DEFAULT_CORDS.z, string objectName = DEFAULT_OBJ_NAME, string objectTag = DEFAULT_TAG) {
    this->id = id;
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