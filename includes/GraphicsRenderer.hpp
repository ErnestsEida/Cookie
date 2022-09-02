#pragma once

#include "GameObject.hpp"
#include "Animation.hpp"
#include <iostream>
#include <map>

using namespace std;

enum ShapeType {
    Circle,
    Rectangle,
};

class GraphicsRenderer : public GameObject {
private:
    Vector2f origin;
    Animation* animation = NULL;
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
        this->setDrawableOrigin(this->origin.x, this->origin.y);
    }

    void addShape(Shape* shape){
        this->addDrawable(dynamic_cast<Drawable*>(shape));
        this->setDrawableOrigin(this->origin.x, this->origin.y);
    }

    void addSprite(string pathToSpritesheet, int frame_width, int frame_height, int frame_count) {
        if (this->animation != NULL) {
            this->clearDrawables();
        }
        this->animation = new Animation(pathToSpritesheet, frame_width, frame_height, frame_count);
        this->addDrawable(dynamic_cast<Drawable*>(this->animation->getSprite()));
    }

    void setDrawableOrigin(float x, float y) {
        this->origin = Vector2f(x, y);
        for(int i = 0; i < this->getDrawables().size(); i++){ 
            Transformable* asTransformable = dynamic_cast<Transformable*>(this->getDrawables()[i]);
            asTransformable->setOrigin(this->origin);
        }
    }

    void OnStart() override {}
    void OnUpdate() override {
        if (this->animation != NULL) {
            this->animation->TryNextSprite();
        }
    }
};