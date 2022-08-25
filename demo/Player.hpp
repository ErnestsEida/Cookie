#pragma once

#include "../includes/GameObject.hpp"
#include "../includes/Gametime.hpp"

class Player : public GameObject {
private:
    const float GRAVITY = 9.71f;

    float speed = 100;
    int vsp = 0;
public:
    Player(int x, int y) : GameObject(x, y) {
        this->setCollider(50, 50);
        RectangleShape *shape = new RectangleShape(Vector2f(50, 50));
        this->addDrawable(shape);
    }

    void OnStart() {}

    void OnUpdate() {
        float real_speed = speed * Gametime::deltaTime;
        int hsp = Keyboard::isKeyPressed(Keyboard::D) - Keyboard::isKeyPressed(Keyboard::A);
        int vsp = Keyboard::isKeyPressed(Keyboard::S) - Keyboard::isKeyPressed(Keyboard::W);
        float real_x = hsp * real_speed;
        float real_y = vsp * real_speed;
        if (GameObject::isCollidingAtPoint(this->getX(), this->getCollider()->bottom() + real_y, "child")) {
            real_y = 0;
        }
        // vsp += GRAVITY;
        this->Move(real_x, real_y);
    }
};