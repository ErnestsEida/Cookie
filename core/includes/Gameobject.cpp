#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <iostream>
#include <vector>

using namespace sf;
using namespace std;

const Vector3f DEFAULT_CORDS = Vector3f(0, 0, 0);
const string DEFAULT_OBJ_NAME = "object";
const string DEFAULT_TAG = "";

class GameObject {
private:
  bool isChild = false;

  vector<GameObject*> children;
  vector<Drawable*> drawables;
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

  vector<Drawable*> getDrawables() {
    vector<Drawable*> drawables = vector<Drawable*>();
    drawables.insert(drawables.end(), this->drawables.begin(), this->drawables.end());
    return drawables;
  }

  void PushChild(GameObject* obj) {
    obj->isChild = true;
    this->children.push_back(obj);
  }

  // Virtual Methods

  virtual void Update() = 0;

  // STATIC METHODS
  // 
  //
};