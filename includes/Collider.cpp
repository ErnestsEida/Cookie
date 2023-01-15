#pragma once
#include <iostream>

#include <SFML/Graphics.hpp>

#include "GameObject.cpp"
#include "Alerts.cpp"

using namespace std;
using namespace sf;

class Collider : public GameObject {
private:
    FloatRect* collision_rect;
    Vector2f collision_size;
    RectangleShape* debugShape;
public:
    // -2147483647 used for Z-index as max INT value, to ensure that nothing can be drawn on top of it
    Collider(Vector2f size, bool debug_mode = false) : GameObject(-size.x / 2, -size.y / 2, -2147483647) {
        this->collision_rect = new FloatRect(this->x, this->y, size.x, size.y);
        this->collision_size = size;

        if (debug_mode) {
            this->debugShape = new RectangleShape(size);
            debugShape->setOutlineColor(Color::Red);
            debugShape->setOutlineThickness(1);
            debugShape->setFillColor(Color(255,255,255,0));
            this->AddDrawable(debugShape);
        }
    }

    void Update() override {
        if (this->parent == nullptr) Alerts::Error("Collider has to be a child of a gameobject!");
        this->collision_rect->left = this->x;
        this->collision_rect->top = this->y;
    }
};