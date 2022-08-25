#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class Collider {
private:
    FloatRect* area;
    float width, height;
    void* holder;
public:
    Collider(float width = 1.0f, float height = 1.0f) {
        this->width = width;
        this->height = height;
        this->area = new FloatRect(0, 0, width, height);
    }

    void setPosition(float x, float y) {
        this->area->left = x;
        this->area->top = y;
    }

    void setHolder(void* holder) { this->holder = holder; }

    void* getHolder() { return this->holder; }
    FloatRect* getArea() { return this->area; }
    float bottom() { return this->area->top + height; }
    float right() { return this->area->left + width; }
};