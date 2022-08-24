#pragma once

#include "../includes/GameObject.hpp"

class Player : public GameObject {
public:
    Player(int x, int y) : GameObject(x, y) {
        RectangleShape *shape = new RectangleShape(Vector2f(50, 50));
        this->addDrawable(shape);
    }

    void OnStart() {

    }

    void OnUpdate() {
        this->setX(this->getX() + 0.5f);
    }
};