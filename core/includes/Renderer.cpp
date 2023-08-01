#pragma once
#include "Gameobject.cpp"
#include "Animation.cpp"

enum ShapeType {
  Circle,
  Rectangle,
};

class Renderer : public GameObject {
private:
  Drawable* mainDrawable = nullptr;
  Animation* animation = nullptr;

public:
  void SetShape(Vector2f size = Vector2f(10, 10), ShapeType shape_type = ShapeType::Circle) {
    if (shape_type == ShapeType::Circle) {
      CircleShape* shape = new CircleShape(size.x);
      this->mainDrawable = shape;
    } else {
      RectangleShape* shape = new RectangleShape(size);
      this->mainDrawable = shape;
    }
  }

  void SetShape(Shape* shape) {
    this->mainDrawable = shape;
  }

  void SetAnimation(Animation* animation) {
    this->animation = animation;
    this->mainDrawable = this->animation->GetFrame();
  }

  void FreeDrawables() {
    this->mainDrawable = nullptr;
    this->drawables.clear();
    this->drawables.shrink_to_fit();
  }

  void Update() override {
    if (this->mainDrawable != nullptr && this->drawables.size() == 0) {
      this->PushDrawable(this->mainDrawable);
    } else if (this->mainDrawable == nullptr && this->drawables.size() > 0) {
      this->FreeDrawables();
    } else {
      if (this->animation != nullptr) {
        this->mainDrawable = this->animation->GetFrame();
        this->animation->NextFrame();
      }
    }
  }
};