#pragma once
#include <SFML/Graphics.hpp>

#include <iostream>
#include <vector>

using namespace sf;
using namespace std;

const Vector3f DEFAULT_CORDS = Vector3f(0, 0, 0);

class GameObject {
private:
  bool isChild = false;

  vector<GameObject*> children;
  vector<Drawable*> drawables;
public:
  float x = DEFAULT_CORDS.x;
  float offset_x = DEFAULT_CORDS.x;
  float y = DEFAULT_CORDS.y;
  float offset_y = DEFAULT_CORDS.y;
  int z = DEFAULT_CORDS.z;

  string objectName;
  string objectTag;
  
  bool isVisible = true;

  virtual void OnFrame() = 0;
};