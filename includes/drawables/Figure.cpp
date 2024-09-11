#pragma once

#include <SFML/Graphics.hpp>
#include "BaseDrawable.cpp"

enum ShapeType {
  Rectangle,
  Circle,
};

class Figure : public BaseDrawable {
  Figure() : BaseDrawable() {
    
  }
};