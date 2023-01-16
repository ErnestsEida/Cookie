#pragma once
#include <iostream>
#include "../../../includes/CookieEngine.cpp"
#include "../../../includes/GameObject.cpp"
#include "../../../includes/Scene.cpp"
#include "../../../includes/SpriteRenderer.cpp"
#include "../../../includes/Gametime.cpp"
#include "../../../includes/Input.cpp"
#include "../../../includes/Animation.cpp"
#include "../../../includes/Collider.cpp"

#include "./Scene2.cpp"

using namespace std;

class Player : public GameObject {
private:
    Animation* runAnimation = new Animation("./sprites/run.png", Vector2i(48, 48), 6, true);
    SpriteRenderer* renderer;
    Collider* collider;

public:
    Player() : GameObject(100, 100, 1, "Player", "player") {
        this->renderer = new SpriteRenderer();
        this->renderer->SetAnimation(this->runAnimation);
        this->renderer->SetOrigin(Origin::Center);

        this->collider = new Collider(Vector2f(24, 38), true);
        
        this->AddChild(this->collider);
        this->AddChild(renderer);
    }

    void Update() override {
        float hsp = 0;
        if (Input::OnKey(Keyboard::Key::D)) {
            hsp += 100 * Gametime::deltaTime;
            this->renderer->SetScale(Vector2f(1, 1));
        } else if (Input::OnKey(Keyboard::Key::A)) {
            hsp -= 100 * Gametime::deltaTime;
            this->renderer->SetScale(Vector2f(-1, 1));
        }
        this->x += hsp;

        if (Input::OnKeyDown(Keyboard::Key::Escape)) {
            CookieEngine::singleton->CloseGame();
        }

        if (Input::OnKeyDown(Keyboard::Key::Q)) CookieEngine::singleton->SetScene(new Scene2());
    }
};