#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class Collider {
private:
    FloatRect* area;
    float width, height;
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

    FloatRect* getArea() { return this->area; }
    float bottom() { return this->area->top + height; }
    float right() { return this->area->left + width; }
};