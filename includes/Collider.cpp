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
    static vector<Collider*> current_colliders;

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
        Collider::current_colliders.push_back(this);
    }

    ~Collider() {
        cout << "Collider Delete" << endl;
    }

    FloatRect* GetColliderRect() {
        return this->collision_rect;
    }

    float Left() {
        return this->collision_rect->left;
    }

    float Right() {
        return this->collision_rect->left + this->collision_rect->width;
    }

    float Top() {
        return this->collision_rect->top;
    }

    float Bottom() {
        return this->collision_rect->top + this->collision_rect->height;
    }

    Collider* isColliding(string tag = "") {
        for(size_t i = 0; i < Collider::current_colliders.size(); i++) {
            Collider* collider = Collider::current_colliders.at(i);
            if ((collider->parent->tag == tag || tag == "") && this != collider) {
                if (this->collision_rect->intersects(*collider->GetColliderRect())) return collider;
            }
        }
        return nullptr;
    }

    bool IsCollidingAtPoint(float point_x, float point_y) {
        return this->collision_rect->contains(point_x, point_y);
    }

    void Update() override {
        if (this->parent == nullptr) Alerts::Error("Collider has to be a child of a gameobject!");
        this->collision_rect->left = this->x;
        this->collision_rect->top = this->y;
    }
};

vector<Collider*> Collider::current_colliders = vector<Collider*>(); 