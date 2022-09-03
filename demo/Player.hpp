#pragma once

#include "../includes/GameObject.hpp"
#include "../includes/Gametime.hpp"
#include "Child.hpp"
#include "../includes/GraphicsRenderer.hpp"

class Player : public GameObject {
private:
    const float GRAVITY = 9.71f;

    float speed = 150;
    int vsp = 0;
public:
    Player(int x, int y) : GameObject(x, y) {
        this->setCollider(32, 32);
        GraphicsRenderer* renderer = new GraphicsRenderer(0, 0);
        renderer->addSprite("./demo/sprites/test.png", 32, 32, 4);
        renderer->setDrawableOrigin(0, 0);
        this->addChild(renderer);
    }

    void OnStart() {}

    void OnUpdate() {
        float real_speed = speed * Gametime::deltaTime;
        int hsp = Keyboard::isKeyPressed(Keyboard::D) - Keyboard::isKeyPressed(Keyboard::A);
        int vsp = Keyboard::isKeyPressed(Keyboard::S) - Keyboard::isKeyPressed(Keyboard::W);
        float real_x = hsp * real_speed;
        float real_y = vsp * real_speed;
        if (GameObject::isCollidingAtPoint(this->getX(), this->getCollider()->bottom() + real_y, "child") || GameObject::isCollidingAtPoint(this->getX(), this->getY() + real_y, "child")) {
            real_y = 0;
        }

        if (GameObject::isCollidingAtPoint(this->getX() + real_x, this->getY(), "child") || GameObject::isCollidingAtPoint(this->getX() + real_x, this->getY() + this->getCollider()->getArea()->height, "child")){
            real_x = 0;
        }
        // vsp += GRAVITY;
        this->Move(real_x, real_y);
    }
};