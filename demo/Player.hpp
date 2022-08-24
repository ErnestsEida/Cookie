#pragma once

#include "../includes/GameObject.hpp"
#include "../includes/Gametime.hpp"
#include "Child.hpp"

class Player : public GameObject {
private:
    int speed = 1;
public:
    Player(int x, int y) : GameObject(x, y) {
        this->setCollider(50, 50);
        RectangleShape *shape = new RectangleShape(Vector2f(50, 50));
        this->addDrawable(shape);

        Child* child = new Child(0, 100);
        this->addChild(child);
    }

    void OnStart() {

    }

    void OnUpdate() {
        if (this->getX() >= 500) speed = -1;
        else if (this->getX() <= 0) speed = 1;
        this->setX(this->getX() + speed);

        cout << this->getCollider()->bottom() << endl;
    }
};