#pragma once

#include "Component.hpp"
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

const int DEFAULT_SIZE = 5;

class GameShape : public Component {
private:
    Transformable* self;
public:
    enum ShapeType {
        Circle,
        Rectangle,
    };

    GameShape(ShapeType type) {
        if (type == ShapeType::Circle) {
            CircleShape* shape = new CircleShape(DEFAULT_SIZE);
            this->self = shape;
        } else if (type == ShapeType::Rectangle) {
            RectangleShape* shape = new RectangleShape(Vector2f(DEFAULT_SIZE, DEFAULT_SIZE));
            this->self = shape;
        }
        this->AddDrawable(this->self);
    }

    GameShape(ShapeType type, int val1, int val2 = DEFAULT_SIZE) {
        if (type == ShapeType::Circle) {
            CircleShape* shape = new CircleShape(val1);
            this->self = shape;
        } else if (type == ShapeType::Rectangle) {
            RectangleShape* shape = new RectangleShape(Vector2f(val1, val2));
            this->self = shape;
        }
        this->AddDrawable(this->self);
    }

    void Trigger() override {}
};