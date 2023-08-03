#pragma once
#include <SFML/Graphics.hpp>
#include "Gameobject.cpp"
#include "Alerts.cpp"

class Viewport {
public:
  View* view = nullptr;
  GameObject* following = nullptr;

  Viewport(Vector2f size = Vector2f(-1, -1)) {
    Vector2f real_size(0, 0); 
    
    real_size.x = size.x < 0 ? 1280 : size.x;
    real_size.y = size.y < 0 ? 720 : size.y;
    Vector2f center = Vector2f(real_size.x / 2, real_size.y / 2);
    
    this->view = new View(center, real_size);
  }

  void ChangeSize(float width, float height) {
    if (this->view == nullptr) Alerts::Error("Trying to change Viewports attributes, without it being initialized");
    Vector2f newSize(width, height);
    this->view->setSize(newSize);
  }

  void UpdateLocation(float x, float y) {
    if (this->view == nullptr) Alerts::Error("Trying to change Viewports attributes, without it being initialized");
    Vector2f newCenter(x, y);
    this->view->setCenter(newCenter);
  }
};