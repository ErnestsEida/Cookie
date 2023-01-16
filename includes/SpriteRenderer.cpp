#pragma once
#include <SFML/Graphics.hpp>

#include "GameObject.cpp"
#include "Alerts.cpp"
#include "Animation.cpp"

using namespace sf;

enum Origin {
    TopLeft,
    TopRight,
    TopCenter,
    CenterLeft,
    CenterRight,
    Center,
    BottomLeft,
    BottomRight,
    BottomCenter,
};

class SpriteRenderer : public GameObject {
private:
    Drawable* sprite = nullptr;
    Animation* animation = nullptr;
    bool alertThrown = false;
    Vector2i spriteSize;
public:
    void SetCircle(float radius) {
        CircleShape* shape = new CircleShape(radius);
        shape->setFillColor(Color::White);
        this->sprite = shape;
        this->spriteSize = Vector2i(radius * 2, radius * 2);
    }

    void SetRectangle(float width, float height) {
        RectangleShape* shape = new RectangleShape(Vector2f(width, height));
        shape->setFillColor(Color::White);
        this->sprite = shape;
        this->spriteSize = Vector2i(width, height);
    }

    void SetAnimation(Animation* animation) {
        this->animation = animation;
        this->sprite = this->animation->GetFrame();
        this->spriteSize = this->animation->GetSize();
    }

    void SetScale(Vector2f scale) {
        Transformable* asTransformable = dynamic_cast<Transformable*>(this->sprite);
        asTransformable->setScale(scale);
    }

    void SetOrigin(Vector2f origin) {
        Transformable* asTransformable = dynamic_cast<Transformable*>(this->sprite);
        asTransformable->setOrigin(origin);
    }

    void SetOrigin(Origin origin_type) {
        Vector2f newOrigin;

        switch(origin_type) {
            case Origin::TopLeft:
                newOrigin = Vector2f(0, 0);
                break;
            case Origin::TopCenter:
                newOrigin = Vector2f(this->spriteSize.x / 2, 0);
                break;
            case Origin::TopRight:
                newOrigin = Vector2f(this->spriteSize.x, 0);
                break;
            case Origin::Center:
                newOrigin = Vector2f(this->spriteSize.x / 2, this->spriteSize.y / 2);
                break;
            case Origin::CenterLeft:
                newOrigin = Vector2f(0, this->spriteSize.y / 2);
                break;
            case Origin::CenterRight:
                newOrigin = Vector2f(this->spriteSize.x, this->spriteSize.y / 2);
                break;
            case Origin::BottomCenter:
                newOrigin = Vector2f(this->spriteSize.x / 2, this->spriteSize.y);
                break;
            case Origin::BottomLeft:
                newOrigin = Vector2f(0, this->spriteSize.y);
                break;
            case Origin::BottomRight:
                newOrigin = Vector2f(this->spriteSize.x, this->spriteSize.y);
                break;
        }

        this->SetOrigin(newOrigin);
    }

    int GetCurrentFrame() {
        if (this->animation == nullptr) {
            Alerts::Warning("Trying to access current frame without animation set!");
            return -1;
        } else {
            return this->animation->current_frame;
        }
    }

    SpriteRenderer() : GameObject() {}

    void Update() override {
        if (this->animation != nullptr) {
            this->sprite = this->animation->GetFrame();
            this->animation->NextFrame();
        }
        this->ClearDrawables();
        this->AddDrawable(this->sprite);
    }
};