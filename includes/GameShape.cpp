#include "GameShape.h"

const float DEFAULT_SIZE = 5;

GameShape::GameShape(ShapeType type){
    if (type == ShapeType::Circle){ // CREATE CIRCLE
        CircleShape* shape = new CircleShape(DEFAULT_SIZE);
        this->object_as_drawable = shape;
        this->object_as_transformable = shape;
    } else if (type == ShapeType::Rectangle){ // CREATE RECTANGLE
        RectangleShape* shape = new RectangleShape(Vector2f(DEFAULT_SIZE, DEFAULT_SIZE));
        this->object_as_drawable = shape;
        this->object_as_transformable = shape;
    }
}

GameShape::GameShape(ShapeType type, float value1){
    if (type == ShapeType::Circle){ // CREATE CIRCLE
        CircleShape* shape = new CircleShape(value1);
        this->object_as_drawable = shape;
        this->object_as_transformable = shape;
    } else if (type == ShapeType::Rectangle){ // CREATE RECTANGLE
        RectangleShape* shape = new RectangleShape(Vector2f(value1, value1));
        this->object_as_drawable = shape;
        this->object_as_transformable = shape;
    }
}

GameShape::GameShape(ShapeType type, float value1, float value2){
    if (type == ShapeType::Circle){ // CREATE CIRCLE
        CircleShape* shape = new CircleShape(value1);
        this->object_as_drawable = shape;
        this->object_as_transformable = shape;
    } else if (type == ShapeType::Rectangle){ // CREATE RECTANGLE
        RectangleShape* shape = new RectangleShape(Vector2f(value1, value2));
        this->object_as_drawable = shape;
        this->object_as_transformable = shape;
    }
}

Transformable* GameShape::GetAsTransformable() const {
    return this->object_as_transformable;
}