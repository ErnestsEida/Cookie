#pragma once

#include <SFML/Graphics.hpp>
#include "BaseDrawable.cpp"

enum ShapeType {
  Rectangle,
  Circle,
};

class Figure : public BaseDrawable {
private:
  ShapeType type;

  void applyProps() {
    BaseDrawable::applyProps();
    Shape* shape = dynamic_cast<Shape*>(this->drawable);
    shape->setFillColor(Color::White);
  }

  void BuildShape() {
    if (this->type == ShapeType::Rectangle) 
    { 
      RectangleShape* holder = new RectangleShape();
      holder->setSize(this->size);
      this->drawable = holder;
    } 
    else if (this->type == ShapeType::Circle) 
    {
      CircleShape* holder = new CircleShape();
      holder->setRadius(this->size.x);
      this->drawable = holder;
    }

    this->applyProps();
  }
public:
  Figure(Vector2f size = Vector2f(0, 0), ShapeType type = ShapeType::Rectangle) : BaseDrawable() {
    this->type = type;
    this->size = size;
    this->BuildShape();
    this->addDrawable(this->drawable);
  }

  virtual void setColor(Color color) final {
    Shape* temp = dynamic_cast<Shape*>(this->drawable);
    temp->setFillColor(color);
  }
};