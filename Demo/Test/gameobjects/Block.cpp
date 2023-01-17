#pragma once
#include "../../../includes/CookieEngine.cpp"
#include "../../../includes/GameObject.cpp"
#include "../../../includes/Scene.cpp"
#include "../../../includes/SpriteRenderer.cpp"
#include "../../../includes/Gametime.cpp"
#include "../../../includes/Input.cpp"
#include "../../../includes/Animation.cpp"
#include "../../../includes/Collider.cpp"

class Block : public GameObject {
private:
    Collider* collider;
    SpriteRenderer* renderer;
public:
    Block(float x, float y) : GameObject(x, y, 1, "Block", "block") {
        collider = new Collider(Vector2f(50, 50), true);
        renderer = new SpriteRenderer();
        renderer->SetRectangle(50, 50);
        renderer->SetOrigin(Origin::Center);

        this->AddChild(this->renderer);
        this->AddChild(this->collider);
    }

    void Update() override {}
};