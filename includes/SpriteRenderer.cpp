#pragma once
#include <SFML/Graphics.hpp>

#include "GameObject.cpp"
#include "Alerts.cpp"

using namespace sf;

class SpriteRenderer : public GameObject {
private:
    Drawable* sprite = nullptr;
    bool alertThrown = false;
public:
    void SetCircle(float radius) {
        CircleShape* shape = new CircleShape(radius);
        shape->setFillColor(Color::White);
        this->sprite = shape;
    }

    void SetRectangle(float width, float height) {
        RectangleShape* shape = new RectangleShape(Vector2f(width, height));
        shape->setFillColor(Color::White);
        this->sprite = shape;
    }

    SpriteRenderer() : GameObject() {}

    void Update() override {
        if (this->sprite == nullptr) {
            if (!alertThrown ) {
                Alerts::Warning("SpriteRenderer was created, but no sprite was set!");
                this->alertThrown = true;
            } 
        } else {
            this->ClearDrawables();
            this->AddDrawable(this->sprite);
        }
    }
};