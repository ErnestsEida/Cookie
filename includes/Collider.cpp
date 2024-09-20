#pragma once

#include <iostream>
#include <vector>

#include "Gameobject.cpp"

using namespace std;

typedef void(*Callback)();


class Collider : public GameObject {
private:
  FloatRect area;
  RectangleShape* outline;
  bool isColliding = false;

  Callback onCollision = nullptr;
  Callback inCollision = nullptr;
  Callback exitCollision = nullptr;

  void BuildOutline(Vector2f size) {
    this->outline = new RectangleShape(size);
    this->outline->setFillColor(Color::Transparent);
    this->outline->setOutlineColor(Color::Red);
    this->outline->setOutlineThickness(2);
  }

  void BuildArea(Vector2f size) {
      Vector2f rawCoords = this->realCoords();
      rawCoords.x -= size.x / 2;
      rawCoords.y += size.y / 2;
      this->area = FloatRect(rawCoords, size);
  }

  Vector2f realCoords() {
    Vector2f rawCoords = GameObject::realCoords();
  }
public:
  Collider(Vector2f size, Vector2f offset = Vector2f(0, 0), string tag = "default") : GameObject(offset.x, offset.y) {
    this->BuildArea(size);
    this->BuildOutline(size);
    this->addDrawable(this->outline);
  }

  void setOutline(bool isVisible) {
    this->isVisible = isVisible;
  }

  virtual void beforeUpdate() final {
    Vector2f coords = this->realCoords();
    this->area.top = coords.x;
    this->area.left = coords.y;
  }

  virtual void onUpdate() final {
    // Check for collisions & trigger callbacks
  }
};
