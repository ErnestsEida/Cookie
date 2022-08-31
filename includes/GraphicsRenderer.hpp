#pragma once

#include "GameObject.hpp"
#include <iostream>
#include <map>

using namespace std;

enum ShapeType {
    Circle,
    Rectangle,
};

class GraphicsRenderer : public GameObject {
private:
    map<string, bool> flags = {
        {"sprite", false},
        {"shape", false},
    };
    Vector2f origin;
public:
    GraphicsRenderer(float x, float y, float z = 0) : GameObject(x, y, z) {}

    void addShape(ShapeType type, float value1 = 0, float value2 = 0) {
        if (type == ShapeType::Circle) {
            CircleShape* shape = new CircleShape(value1);
            this->addDrawable(shape);
        } else if (type == ShapeType::Rectangle) {
            RectangleShape* shape = new RectangleShape(Vector2f(value1, value2));
            this->addDrawable(shape);
        }
        this->flags.at("shape") = true;
    }

    void addShape(Shape* shape){
        this->addDrawable(dynamic_cast<Drawable*>(shape));
    }

    void setDrawableOrigin(float x, float y) {
        this->origin = Vector2f(x, y);
        for(int i = 0; i < this->getDrawables().size(); i++){ 
            Transformable* asTransformable = dynamic_cast<Transformable*>(this->getDrawables()[i]);
            asTransformable->setOrigin(this->origin);
        }
    }

    void OnStart() override {}
    void OnUpdate() override {}
};