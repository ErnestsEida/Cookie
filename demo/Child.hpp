#pragma once

#include "../includes/GameObject.hpp"

class Child : public GameObject {
public:
    Child(int x, int y) : GameObject(x, y) {
        RectangleShape *shape = new RectangleShape(Vector2f(50, 50));
        shape->setFillColor(Color::Red);
        this->addDrawable(shape);
    }

    void OnStart() {

    }

    void OnUpdate() {
    }
};