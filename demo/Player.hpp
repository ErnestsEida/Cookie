#pragma once

#include "../includes/GameObject.hpp"
#include "../includes/Gametime.hpp"
#include "Child.hpp"

class Player : public GameObject {
private:
    int speed = 5;
public:
    Player(int x, int y) : GameObject(x, y) {
        RectangleShape *shape = new RectangleShape(Vector2f(50, 50));
        this->addDrawable(shape);
        Child* f = new Child(0, 50);
        this->addChild(f);
    }

    void OnStart() {

    }

    void OnUpdate() {
        if (this->getX() >= 500) speed = -5;
        else if (this->getX() <= 0) speed = 5;
        this->setX(this->getX() + speed);
    }
};