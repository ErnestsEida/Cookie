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
  Vector2f(-1, -1), Vector2f(0, -1), Vector2f(1, -1),
  Vector2f(-1, 0), Vector2f(0, 0), Vector2f(1, 0),
  Vector2f(-1, 1), Vector2f(0, 1), Vector2f(1, 1),
};

class BaseDrawable : public GameObject {
protected:
  Vector2f origin = ORIGIN_MAP[OriginPoint::CENTER];
  Vector2f scale = Vector2f(1, 1);
  float rotation = 0;
  Drawable* drawable;

public:
  BaseDrawable() {
    this->addDrawable(this->drawable);
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