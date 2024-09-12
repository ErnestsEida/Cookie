#pragma once

#include <SFML/Graphics.hpp>
#include "../Gameobject.cpp"

using namespace sf;

enum OriginPoint {
  TOP_LEFT, TOP_CENTER, TOP_RIGHT,
  CENTER_LEFT, CENTER, CENTER_RIGHT,
  BOTTOM_LEFT, BOTTOM_CENTER, BOTTOM_RIGHT
};

const Vector2f ORIGIN_MAP[9] = {
  Vector2f(0, 0), Vector2f(1, 0), Vector2f(2, 0),
  Vector2f(0, 1), Vector2f(1, 1), Vector2f(2, 1),
  Vector2f(0, 2), Vector2f(1, 2), Vector2f(2, 2),
};

class BaseDrawable : public GameObject {
private:
  Vector2f CalculateOrigin() {
    float half_x = this->size.x / 2;
    float half_y = this->size.y / 2;

    float real_x = half_x * this->origin.x;
    float real_y = half_y * this->origin.y;

    return Vector2f(real_x, real_y);
  }

protected:
  Vector2f origin = ORIGIN_MAP[OriginPoint::TOP_LEFT];
  Vector2f scale = Vector2f(1, 1);
  Vector2f size = Vector2f(0, 0);
  float rotation = 0;
  Drawable* drawable = nullptr;

  void applyProps() {
    Transformable* transformable = dynamic_cast<Transformable*>(this->drawable);
    transformable->setOrigin(CalculateOrigin());
    transformable->setScale(this->scale);
    transformable->setRotation(this->rotation);
  }

public:
  BaseDrawable() {}

  virtual void setSize(Vector2f size) final {
    this->size = size;
  }

  virtual void setOrigin(OriginPoint point) final {
    this->origin = ORIGIN_MAP[point];
  }

  virtual void setCustomOrigin(Vector2f origin) final {
    this->origin = origin;
  }

  virtual void setScale(Vector2f scale) final {
    this->scale = scale;
  }

  virtual void setRotation(float angle) final {
    this->rotation = angle;
  }
};